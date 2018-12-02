/*
 *  libzvbi -- Extended Data Service demultiplexer
 *
 *  Copyright (C) 2000-2005 Michael H. Schimek
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Library General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Library General Public License for more details.
 *
 *  You should have received a copy of the GNU Library General Public
 *  License along with this library; if not, write to the 
 *  Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, 
 *  Boston, MA  02110-1301  USA.
 */

/* $Id: xds_demux.c,v 1.11 2008/02/19 00:35:23 mschimek Exp $ */

#include "libzvbi.h"
#include <CoreLib/VxDebug.h>

#include "site_def.h"


#include "misc.h"		/* vbi_log_printf() */
#include "hamm.h"		/* vbi_ipar8() */
#include "tables.h"		/* vbi_rating/prog_type_string() */
#include "xds_demux.h"

/**
 * @addtogroup XDSDemux Extended Data Service (XDS) demultiplexer
 * @ingroup LowDec
 * @brief Separating XDS data from a Closed Caption stream
 *   (EIA 608).
 */

#ifndef XDS_DEMUX_LOG
#define XDS_DEMUX_LOG 0
#endif


static void xdump( const vbi_xds_packet * xp, char * retMsgBuf )
{
	unsigned int i;

	for (i = 0; i < xp->buffer_size; ++i)
		sprintf( &retMsgBuf[ strlen( retMsgBuf ) ], " %02x", xp->buffer[i]);

	strcat( retMsgBuf, " \'" );

	for (i = 0; i < xp->buffer_size; ++i)
		sprintf( &retMsgBuf[ strlen( retMsgBuf ) ], " %c", _vbi_to_ascii( xp->buffer[ i ] ) );

	strcat( retMsgBuf, " \'" );
}

/** @internal */
void
_vbi_xds_packet_dump		(const vbi_xds_packet *	xp,
				 FILE *			fp)
{
	static const char *month_names [] = {
		"0?", "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug",
		"Sep", "Oct", "Nov", "Dec", "13?", "14?", "15?"
	};
	static const char *map_type [] = {
		"unknown", "mono", "simulated stereo", "stereo",
		"stereo surround", "data service", "unknown", "none"
	};
	static const char *sap_type [] = {
		"unknown", "mono", "video descriptions", "non-program audio",
		"special effects", "data service", "unknown", "none"
	};
	static const char *language [] = {
		"unknown", "English", "Spanish", "French", "German",
		"Italian", "Other", "none"
	};
	static const char *cgmsa [] = {
		"copying permitted", "-", "one copy allowed",
		"no copying permitted"
	};
	static const char *scrambling [] = {
		"no pseudo-sync pulse",
		"pseudo-sync pulse on; color striping off",
		"pseudo-sync pulse on; 2-line color striping on",
		"pseudo-sync pulse on; 4-line color striping on"
	};
	static const char *day_names [] = {
		"0?", "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"
	};
	unsigned int i;

	assert (NULL != xp);
	assert (NULL != fp);

	char totalMsg[ MAX_ERR_MSG_SIZE ];
	totalMsg[ 0 ] = 0;


	sprintf( &totalMsg[strlen(totalMsg) ],  "XDS packet 0x%02x%02x ",
		 xp->xds_class * 2 + 1, xp->xds_subclass);

	if ( ( xp->xds_class >= VBI_XDS_PROGRAM_DESCRIPTION_BEGIN )
		&& ( xp->xds_class <= VBI_XDS_PROGRAM_DESCRIPTION_END - 1 ) )
	{
		sprintf( &totalMsg[ strlen( totalMsg ) ], "description %u)",
			(unsigned int)xp->xds_subclass
			- (unsigned int)
			VBI_XDS_PROGRAM_DESCRIPTION_BEGIN );
		xdump( xp, &totalMsg[ strlen( totalMsg ) ] );
	}
	else
	{
		switch ( xp->xds_class ) {
		case VBI_XDS_CLASS_CURRENT:
			strcat( &totalMsg[ strlen( totalMsg ) ], "(cur. program " );

			/* fall through */

		case VBI_XDS_CLASS_FUTURE:
			if ( VBI_XDS_CLASS_FUTURE == xp->xds_class )
				strcat( &totalMsg[ strlen( totalMsg ) ], "(fut. program " );

			switch ( xp->xds_subclass ) {
			case VBI_XDS_PROGRAM_ID:
			{
				unsigned int month, day, hour, min;

				strcat( &totalMsg[ strlen( totalMsg ) ], "id)" );
				xdump( xp, &totalMsg[ strlen( totalMsg ) ]  );

				if ( 4 != xp->buffer_size ) {
				invalid:
					strcat( &totalMsg[ strlen( totalMsg ) ], " (invalid)" );
					break;
				}

				month = xp->buffer[ 3 ] & 15;
				day = xp->buffer[ 2 ] & 31;
				hour = xp->buffer[ 1 ] & 31;
				min = xp->buffer[ 0 ] & 63;

				if ( month == 0 || month > 12
					|| day == 0 || day > 31
					|| hour > 23 || min > 59 )
					goto invalid;

				sprintf( &totalMsg[ strlen( totalMsg ) ], " (%d %s %02d:%02d UTC,",
					day, month_names[ month ], hour, min );

				sprintf( &totalMsg[ strlen( totalMsg ) ], " D=%d L=%d Z=%d T=%d)",
					!!( xp->buffer[ 1 ] & 0x20 ),
					!!( xp->buffer[ 2 ] & 0x20 ),
					!!( xp->buffer[ 3 ] & 0x20 ),
					!!( xp->buffer[ 3 ] & 0x10 ) );

				break;
			}

			case VBI_XDS_PROGRAM_LENGTH:
			{
				unsigned int lhour, lmin;

				strcat( &totalMsg[ strlen( totalMsg ) ], "length)" );
				xdump( xp, &totalMsg[ strlen( totalMsg ) ] );

				switch ( xp->buffer_size ) {
				case 2:
				case 4:
				case 5:
					break;

				default:
					goto invalid;
				}

				lhour = xp->buffer[ 1 ] & 63;
				lmin = xp->buffer[ 0 ] & 63;

				if ( lmin > 59 )
					goto invalid;

				sprintf( &totalMsg[ strlen( totalMsg ) ], " (%02d:%02d", lhour, lmin );

				if ( xp->buffer_size >= 4 ) {
					unsigned int ehour, emin;

					ehour = xp->buffer[ 3 ] & 63;
					emin = xp->buffer[ 2 ] & 63;

					if ( emin > 59 )
						goto invalid;

					sprintf( &totalMsg[ strlen( totalMsg ) ], " elapsed=%02d:%02d",
						ehour, emin );

					if ( xp->buffer_size >= 5 ) {
						unsigned int esec;

						esec = xp->buffer[ 4 ] & 63;

						if ( esec > 59 )
							goto invalid;

						sprintf( &totalMsg[ strlen( totalMsg ) ], ":%02d", esec );
					}
				}

				sprintf( &totalMsg[ strlen( totalMsg ) ], "%c", ')' );

				break;
			}

			case VBI_XDS_PROGRAM_NAME:
				strcat( &totalMsg[ strlen( totalMsg ) ], "name)" );
				xdump( xp, &totalMsg[ strlen( totalMsg ) ]  );
				break;

			case VBI_XDS_PROGRAM_TYPE:
			{
				unsigned int i;

				strcat( &totalMsg[ strlen( totalMsg ) ], "type)" );
				xdump( xp, &totalMsg[ strlen( totalMsg ) ]  );

				if ( xp->buffer_size < 1 )
					goto invalid;

				strcat( &totalMsg[ strlen( totalMsg ) ], " (" );

				for ( i = 0; i < xp->buffer_size; ++i ) {
					sprintf( &totalMsg[ strlen( totalMsg ) ], ( i > 0 ) ? ", %s" : "%s",
						vbi_prog_type_string
						( VBI_PROG_CLASSF_EIA_608,
							xp->buffer[ i ] ) );
				}

				sprintf( &totalMsg[ strlen( totalMsg ) ], "%c", ')' );

				break;
			}

			case VBI_XDS_PROGRAM_RATING:
			{
				unsigned int r, g;

				strcat( &totalMsg[ strlen( totalMsg ) ], "rating)" );
				xdump( xp, &totalMsg[ strlen( totalMsg ) ]  );

				if ( 2 != xp->buffer_size )
					goto invalid;

				r = xp->buffer[ 0 ] & 7;
				g = xp->buffer[ 1 ] & 7;

				sprintf( &totalMsg[ strlen( totalMsg ) ], " (movie: %s, tv: ",
					vbi_rating_string( VBI_RATING_AUTH_MPAA, r ) );

				if ( xp->buffer[ 0 ] & 0x10 ) {
					const char *s;

					if ( xp->buffer[ 0 ] & 0x20 )
						s = vbi_rating_string
						( VBI_RATING_AUTH_TV_CA_FR, g );
					else
						s = vbi_rating_string
						( VBI_RATING_AUTH_TV_CA_EN, g );

					strcat( &totalMsg[ strlen( totalMsg ) ], s );
				}
				else {
					sprintf( &totalMsg[ strlen( totalMsg ) ], "%s D=%d L=%d S=%d V=%d",
						vbi_rating_string
						( VBI_RATING_AUTH_TV_US, g ),
						!!( xp->buffer[ 0 ] & 0x20 ),
						!!( xp->buffer[ 1 ] & 0x08 ),
						!!( xp->buffer[ 1 ] & 0x10 ),
						!!( xp->buffer[ 1 ] & 0x20 ) );
				}

				sprintf( &totalMsg[ strlen( totalMsg ) ], "%c", ')' );

				break;
			}

			case VBI_XDS_PROGRAM_AUDIO_SERVICES:
				strcat( &totalMsg[ strlen( totalMsg ) ], "audio services)" );
				xdump( xp, &totalMsg[ strlen( totalMsg ) ]  );

				if ( 2 != xp->buffer_size )
					goto invalid;

				sprintf( &totalMsg[ strlen( totalMsg ) ], " (main: %s, %s; second: %s, %s)",
					map_type[ xp->buffer[ 0 ] & 7 ],
					language[ ( xp->buffer[ 0 ] >> 3 ) & 7 ],
					sap_type[ xp->buffer[ 1 ] & 7 ],
					language[ ( xp->buffer[ 1 ] >> 3 ) & 7 ] );

				break;

			case VBI_XDS_PROGRAM_CAPTION_SERVICES:
				strcat( &totalMsg[ strlen( totalMsg ) ], "caption services)" );
				xdump( xp, &totalMsg[ strlen( totalMsg ) ]  );

				if ( xp->buffer_size < 1
					|| xp->buffer_size > 8 )
					goto invalid;

				sprintf( &totalMsg[ strlen( totalMsg ) ], "%c", '(' );

				for ( i = 0; i < xp->buffer_size; ++i ) {
					sprintf( &totalMsg[ strlen( totalMsg ) ], "%sline=%u channel=%u %s %s",
						( 0 == i ) ? "" : ", ",
						( xp->buffer[ i ] & 4 ) ? 284 : 21,
						( xp->buffer[ i ] & 2 ) ? 2 : 1,
						( xp->buffer[ i ] & 1 ) ?
						"text" : "captioning",
						language[ ( xp->buffer[ i ] >> 3 ) & 7 ] );
				}

				sprintf( &totalMsg[ strlen( totalMsg ) ], "%c", ')' );

				break;

			case VBI_XDS_PROGRAM_CGMS:
				strcat( &totalMsg[ strlen( totalMsg ) ], "cgms)" );
				xdump( xp, &totalMsg[ strlen( totalMsg ) ]  );

				if ( 1 != xp->buffer_size )
					goto invalid;

				sprintf( &totalMsg[ strlen( totalMsg ) ], " (%s", cgmsa[ ( xp->buffer[ 0 ] >> 3 ) & 3 ] );

				if ( xp->buffer[ 0 ] & 0x18 )
					sprintf( &totalMsg[ strlen( totalMsg ) ], ", %s",
						scrambling[ ( xp->buffer[ 0 ] >> 1 ) & 3 ] );

				sprintf( &totalMsg[ strlen( totalMsg ) ], ", analog_source=%u)", xp->buffer[ 0 ] & 1 );

				break;

			case VBI_XDS_PROGRAM_ASPECT_RATIO:
			{
				unsigned int first_line, last_line;

				strcat( &totalMsg[ strlen( totalMsg ) ], "aspect)" );
				xdump( xp, &totalMsg[ strlen( totalMsg ) ]  );

				if ( 2 != xp->buffer_size
					&& 3 != xp->buffer_size )
					goto invalid;

				first_line = 22 + ( xp->buffer[ 0 ] & 63 );
				last_line = 262 - ( xp->buffer[ 1 ] & 63 );

				sprintf( &totalMsg[ strlen( totalMsg ) ], " (active picture %u ... %u%s)",
					first_line, last_line,
					( 3 == xp->buffer_size
						&& ( xp->buffer[ 2 ] & 1 ) ) ?
					" anamorphic" : "" );

				break;
			}

			case VBI_XDS_PROGRAM_DATA:
			{
				unsigned int rating;
				unsigned int lhour, lmin;
				unsigned int ehour, emin;

				strcat( &totalMsg[ strlen( totalMsg ) ], "data)" );
				xdump( xp, &totalMsg[ strlen( totalMsg ) ]  );

				/* XXX ok? */
				if ( xp->buffer_size < 10 )
					goto invalid;

				rating = xp->buffer[ 5 ] & 7;

				lhour = xp->buffer[ 7 ] & 63;
				lmin = xp->buffer[ 6 ] & 63;

				if ( lmin > 59 )
					goto invalid;

				ehour = xp->buffer[ 9 ] & 63;
				emin = xp->buffer[ 8 ] & 63;

				if ( emin > 59 )
					goto invalid;

				strcat( &totalMsg[ strlen( totalMsg ) ], " (type: " );

				for ( i = 0; i < 5; ++i ) {
					sprintf( &totalMsg[ strlen( totalMsg ) ], ( i > 0 ) ? ", %s" : "%s",
						vbi_prog_type_string
						( VBI_PROG_CLASSF_EIA_608,
							xp->buffer[ i ] ) );
				}

				sprintf( &totalMsg[ strlen( totalMsg ) ], "; rating: %s; "
					"length: %02d:%02d; "
					"elapsed: %02d:%02d)",
					vbi_rating_string( VBI_RATING_AUTH_MPAA,
						rating ),
					lhour, lmin, ehour, emin );

				/* program name: buffer[10 ... 31] (xdump'ed) */

				break;
			}

			case VBI_XDS_PROGRAM_MISC_DATA:
			{
				unsigned int month, day, hour, min;

				strcat( &totalMsg[ strlen( totalMsg ) ], "misc data)" );
				xdump( xp, &totalMsg[ strlen( totalMsg ) ]  );

				/* XXX ok? */
				if ( 14 != xp->buffer_size )
					goto invalid;

				month = xp->buffer[ 3 ] & 15;
				day = xp->buffer[ 2 ] & 31;
				hour = xp->buffer[ 1 ] & 31;
				min = xp->buffer[ 0 ] & 63;

				if ( month == 0 || month > 12
					|| day == 0 || day > 31
					|| hour > 23 || min > 59 )
					goto invalid;

				sprintf( &totalMsg[ strlen( totalMsg ) ], " (%d %s %02d:%02d UTC, ",
					day, month_names[ month ], hour, min );

				sprintf( &totalMsg[ strlen( totalMsg ) ], " D=%d L=%d Z=%d T=%d",
					!!( xp->buffer[ 1 ] & 0x20 ),
					!!( xp->buffer[ 2 ] & 0x20 ),
					!!( xp->buffer[ 3 ] & 0x20 ),
					!!( xp->buffer[ 3 ] & 0x10 ) );

				sprintf( &totalMsg[ strlen( totalMsg ) ], ", main audio: %s, %s; second: %s, %s;",
					map_type[ xp->buffer[ 4 ] & 7 ],
					language[ ( xp->buffer[ 4 ] >> 3 ) & 7 ],
					sap_type[ xp->buffer[ 5 ] & 7 ],
					language[ ( xp->buffer[ 5 ] >> 3 ) & 7 ] );

				for ( i = 6; i < 8; ++i ) {
					sprintf( &totalMsg[ strlen( totalMsg ) ], "%sline=%u channel=%u %s %s",
						( 6 == i ) ? " caption: " : ", ",
						( xp->buffer[ i ] & 4 ) ? 284 : 21,
						( xp->buffer[ i ] & 2 ) ? 2 : 1,
						( xp->buffer[ i ] & 1 ) ?
						"text" : "captioning",
						language[ ( xp->buffer[ i ] >> 3 ) & 7 ] );
				}

				sprintf( &totalMsg[ strlen( totalMsg ) ], ", call letters: " );
				for ( i = 8; i < 12; ++i ) {
					sprintf( &totalMsg[ strlen( totalMsg ) ], "%c", _vbi_to_ascii( xp->buffer[ i ] ) );
				}

				/* 02 to 69 or 0x20 0x20 */
				sprintf( &totalMsg[ strlen( totalMsg ) ], ", channel: " );
				for ( i = 12; i < 14; ++i ) {
					sprintf( &totalMsg[ strlen( totalMsg ) ], "%c", _vbi_to_ascii( xp->buffer[ i ] ) );
				}

				sprintf( &totalMsg[ strlen( totalMsg ) ], "%c", ')' );

				break;
			}

			case VBI_XDS_PROGRAM_DESCRIPTION_BEGIN:
			case VBI_XDS_PROGRAM_DESCRIPTION_END - 1:
				// this should have been handled in if part of if / else
				vx_assert( 0 );
				break;

			default:
				strcat( &totalMsg[ strlen( totalMsg ) ], "?)" );
				xdump( xp, &totalMsg[ strlen( totalMsg ) ]  );
				break;
			}

			break;

		case VBI_XDS_CLASS_CHANNEL:
			strcat( &totalMsg[ strlen( totalMsg ) ], "(channel " );

			switch ( xp->xds_subclass ) {
			case VBI_XDS_CHANNEL_NAME:
				strcat( &totalMsg[ strlen( totalMsg ) ], "name)" );
				xdump( xp, &totalMsg[ strlen( totalMsg ) ]  );
				break;

			case VBI_XDS_CHANNEL_CALL_LETTERS:
				strcat( &totalMsg[ strlen( totalMsg ) ], "call letters)" );
				xdump( xp, &totalMsg[ strlen( totalMsg ) ]  );
				break;

			case VBI_XDS_CHANNEL_TAPE_DELAY:
			{
				unsigned int hour, min;

				strcat( &totalMsg[ strlen( totalMsg ) ], "tape delay)" );
				xdump( xp, &totalMsg[ strlen( totalMsg ) ]  );

				if ( 2 != xp->buffer_size )
					goto invalid;

				hour = xp->buffer[ 1 ] & 31;
				min = xp->buffer[ 0 ] & 63;

				if ( min > 59 )
					goto invalid;

				sprintf( &totalMsg[ strlen( totalMsg ) ], " (%02d:%02d)", hour, min );

				break;
			}

			case VBI_XDS_CHANNEL_TSID:
			{
				unsigned int tsid;

				strcat( &totalMsg[ strlen( totalMsg ) ], "transmission signal identifier)" );
				xdump( xp, &totalMsg[ strlen( totalMsg ) ]  );

				if ( 4 != xp->buffer_size )
					goto invalid;

				tsid = ( xp->buffer[ 3 ] & 15 ) << 0;
				tsid += ( xp->buffer[ 2 ] & 15 ) << 4;
				tsid += ( xp->buffer[ 1 ] & 15 ) << 8;
				tsid += ( xp->buffer[ 0 ] & 15 ) << 12;

				if ( 0 == tsid )
					goto invalid;

				sprintf( &totalMsg[ strlen( totalMsg ) ], " (0x%04x)", tsid );

				break;
			}

			default:
				strcat( &totalMsg[ strlen( totalMsg ) ], "?)" );
				xdump( xp, &totalMsg[ strlen( totalMsg ) ]  );
				break;
			}

			break;

		case VBI_XDS_CLASS_MISC:
			strcat( &totalMsg[ strlen( totalMsg ) ], "(misc: " );

			switch ( xp->xds_subclass ) {
			case VBI_XDS_TIME_OF_DAY:
				strcat( &totalMsg[ strlen( totalMsg ) ], "time of day)" );
				xdump( xp, &totalMsg[ strlen( totalMsg ) ]  );

				if ( 6 != xp->buffer_size )
					goto invalid;

				sprintf( &totalMsg[ strlen( totalMsg ) ], " (%s, %d %s %d",
					day_names[ xp->buffer[ 4 ] & 7 ],
					xp->buffer[ 2 ] & 31,
					month_names[ xp->buffer[ 3 ] & 15 ],
					1990 + ( xp->buffer[ 5 ] & 63 ) );

				sprintf( &totalMsg[ strlen( totalMsg ) ], " %02d:%02d UTC",
					xp->buffer[ 1 ] & 31,
					xp->buffer[ 0 ] & 63 );

				sprintf( &totalMsg[ strlen( totalMsg ) ], " D=%u L=%u Z=%u T=%u)",
					!!( xp->buffer[ 1 ] & 0x20 ),
					!!( xp->buffer[ 2 ] & 0x20 ),
					!!( xp->buffer[ 3 ] & 0x20 ),
					!!( xp->buffer[ 3 ] & 0x10 ) );

				break;

			case VBI_XDS_IMPULSE_CAPTURE_ID:
				strcat( &totalMsg[ strlen( totalMsg ) ], "capture id)" );
				xdump( xp, &totalMsg[ strlen( totalMsg ) ]  );

				if ( 6 != xp->buffer_size )
					goto invalid;

				sprintf( &totalMsg[ strlen( totalMsg ) ], " (%d %s",
					xp->buffer[ 2 ] & 31,
					month_names[ xp->buffer[ 3 ] & 15 ] );

				sprintf( &totalMsg[ strlen( totalMsg ) ], " %02d:%02d",
					xp->buffer[ 1 ] & 31,
					xp->buffer[ 0 ] & 63 );

				sprintf( &totalMsg[ strlen( totalMsg ) ], " length=%02d:%02d",
					xp->buffer[ 5 ] & 63,
					xp->buffer[ 4 ] & 63 );

				sprintf( &totalMsg[ strlen( totalMsg ) ], " D=%u L=%u Z=%u T=%u)",
					!!( xp->buffer[ 1 ] & 0x20 ),
					!!( xp->buffer[ 2 ] & 0x20 ),
					!!( xp->buffer[ 3 ] & 0x20 ),
					!!( xp->buffer[ 3 ] & 0x10 ) );

				break;

			case VBI_XDS_SUPPLEMENTAL_DATA_LOCATION:
			{
				unsigned int i;

				strcat( &totalMsg[ strlen( totalMsg ) ], "supplemental data)" );
				xdump( xp, &totalMsg[ strlen( totalMsg ) ]  );

				if ( xp->buffer_size < 1 )
					goto invalid;

				sprintf( &totalMsg[ strlen( totalMsg ) ], "%c", '(' );

				for ( i = 0; i < xp->buffer_size; ++i ) {
					sprintf( &totalMsg[ strlen( totalMsg ) ], "%sfield=%u line=%u",
						( 0 == i ) ? "" : ", ",
						!!( xp->buffer[ i ] & 0x20 ),
						xp->buffer[ i ] & 31 );
				}

				sprintf( &totalMsg[ strlen( totalMsg ) ], "%c", ')' );

				break;
			}

			case VBI_XDS_LOCAL_TIME_ZONE:
				strcat( &totalMsg[ strlen( totalMsg ) ], "time zone)" );
				xdump( xp, &totalMsg[ strlen( totalMsg ) ]  );

				if ( 1 != xp->buffer_size )
					goto invalid;

				sprintf( &totalMsg[ strlen( totalMsg ) ], " (UTC%+05d ods=%u)",
					( xp->buffer[ 0 ] & 31 ) * -100,
					!!( xp->buffer[ 0 ] & 0x20 ) );

				break;

			case VBI_XDS_OUT_OF_BAND_CHANNEL:
			{
				unsigned int channel;

				strcat( &totalMsg[ strlen( totalMsg ) ], "out of band channel number)" );
				xdump( xp, &totalMsg[ strlen( totalMsg ) ]  );

				if ( 2 != xp->buffer_size )
					goto invalid;

				channel = ( xp->buffer[ 0 ] & 63 )
					+ ( ( xp->buffer[ 1 ] & 63 ) << 6 );

				sprintf( &totalMsg[ strlen( totalMsg ) ], " (%u)", channel );

				break;
			}

			case VBI_XDS_CHANNEL_MAP_POINTER:
			{
				unsigned int channel;

				strcat( &totalMsg[ strlen( totalMsg ) ], "channel map pointer)" );
				xdump( xp, &totalMsg[ strlen( totalMsg ) ]  );

				if ( 2 != xp->buffer_size )
					goto invalid;

				channel = ( xp->buffer[ 0 ] & 63 )
					+ ( ( xp->buffer[ 1 ] & 63 ) << 6 );

				sprintf( &totalMsg[ strlen( totalMsg ) ], " (%u)", channel );

				break;
			}

			case VBI_XDS_CHANNEL_MAP_HEADER:
			{
				unsigned int n_channels;
				unsigned int version;

				strcat( &totalMsg[ strlen( totalMsg ) ], "channel map header)" );
				xdump( xp, &totalMsg[ strlen( totalMsg ) ]  );

				if ( 4 != xp->buffer_size )
					goto invalid;

				n_channels = ( xp->buffer[ 0 ] & 63 )
					+ ( ( xp->buffer[ 1 ] & 63 ) << 6 );

				version = xp->buffer[ 2 ] & 63;

				sprintf( &totalMsg[ strlen( totalMsg ) ], " (n_channels: %u, version: %u)",
					n_channels, version );

				break;
			}

			case VBI_XDS_CHANNEL_MAP:
			{
				unsigned int channel;
				vbi_bool remapped;

				strcat( &totalMsg[ strlen( totalMsg ) ], "channel map)" );
				xdump( xp, &totalMsg[ strlen( totalMsg ) ]  );

				channel = ( xp->buffer[ 0 ] & 63 )
					+ ( ( xp->buffer[ 1 ] & 31 ) << 6 );

				sprintf( &totalMsg[ strlen( totalMsg ) ], " (channel: %u)", channel );

				remapped = !!( xp->buffer[ 1 ] & 0x20 );

				if ( remapped ) {
					unsigned int tune_channel;

					tune_channel = ( xp->buffer[ 2 ] & 63 )
						+ ( ( xp->buffer[ 3 ] & 63 ) << 6 );

					sprintf( &totalMsg[ strlen( totalMsg ) ], ", remapped to: %u)",
						tune_channel );
				}

				/* channel id: buffer[2 or 4 ... 31] (xdump'ed) */

				sprintf( &totalMsg[ strlen( totalMsg ) ], "%c", ')' );

				break;
			}

			default:
				strcat( &totalMsg[ strlen( totalMsg ) ], "?)" );
				xdump( xp, &totalMsg[ strlen( totalMsg ) ]  );
				break;
			}

			break;

		case VBI_XDS_CLASS_PUBLIC_SERVICE:
			strcat( &totalMsg[ strlen( totalMsg ) ], "(pub. service " );

			switch ( xp->xds_subclass ) {
			case VBI_XDS_WEATHER_BULLETIN:
			{
				unsigned int duration;

				strcat( &totalMsg[ strlen( totalMsg ) ], "weather bulletin)" );
				xdump( xp, &totalMsg[ strlen( totalMsg ) ]  );

				sprintf( &totalMsg[ strlen( totalMsg ) ], " (event category: " );
				for ( i = 0; i < 3; ++i ) {
					sprintf( &totalMsg[ strlen( totalMsg ) ], "%c", _vbi_to_ascii( xp->buffer[ i ] ) );
				}

				/* 3 digit FIPS number. */
				sprintf( &totalMsg[ strlen( totalMsg ) ], ", state: " );
				for ( i = 3; i < 6; ++i ) {
					sprintf( &totalMsg[ strlen( totalMsg ) ], "%c", _vbi_to_ascii( xp->buffer[ i ] ) );
				}

				/* 3 digit FIPS number. */
				sprintf( &totalMsg[ strlen( totalMsg ) ], ", county: " );
				for ( i = 6; i < 9; ++i ) {
					sprintf( &totalMsg[ strlen( totalMsg ) ], "%c", _vbi_to_ascii( xp->buffer[ i ] ) );
				}

				/* 2 digit number of quarter hours */
				duration = ( xp->buffer[ 9 ] & 15 ) * 150
					+ ( xp->buffer[ 10 ] & 15 ) * 15;

				sprintf( &totalMsg[ strlen( totalMsg ) ], ", duration: %02d:%02d)",
					duration / 60, duration % 60 );

				break;
			}

			case VBI_XDS_WEATHER_MESSAGE:
				strcat( &totalMsg[ strlen( totalMsg ) ], "weather message)" );
				xdump( xp, &totalMsg[ strlen( totalMsg ) ]  );
				break;
			}

			break;

		case VBI_XDS_CLASS_RESERVED:
			strcat( &totalMsg[ strlen( totalMsg ) ], "(reserved)" );
			xdump( xp, &totalMsg[ strlen( totalMsg ) ]  );
			break;

		case VBI_XDS_CLASS_UNDEFINED:
			strcat( &totalMsg[ strlen( totalMsg ) ], "(undefined)" );
			xdump( xp, &totalMsg[ strlen( totalMsg ) ]  );
			break;

		default:
			strcat( &totalMsg[ strlen( totalMsg ) ], "(?)" );
			xdump( xp, &totalMsg[ strlen( totalMsg ) ]  );
			break;
		}
	}

	sprintf( &totalMsg[ strlen( totalMsg ) ], "%c", '\n' );
	LogMsg( LOG_DEBUG, totalMsg );
}

/**
 * @param xd XDS demultiplexer context allocated with vbi_xds_demux_new().
 *
 * Resets the XDS demux, useful for example after a channel change.
 *
 * @since 0.2.16
 */
void
vbi_xds_demux_reset		(vbi_xds_demux *	xd)
{
	unsigned int n;
	unsigned int i;

	assert (NULL != xd);

	n = N_ELEMENTS (xd->subpacket) * N_ELEMENTS (xd->subpacket[0]);

	for (i = 0; i < n; ++i)
		xd->subpacket[0][i].count = 0;

	xd->curr_sp = NULL;
}

/**
 * @param xd XDS demultiplexer context allocated with vbi_xds_demux_new().
 * @param buffer Closed Caption character pair, as in struct vbi_sliced.
 *
 * This function takes two successive bytes of a raw Closed Caption
 * stream, filters out XDS data and calls the output function given to
 * vbi_xds_demux_new() when a new packet is complete.
 *
 * You should feed only data from NTSC line 284.
 *
 * @returns
 * @c FALSE if the buffer contained parity errors.
 *
 * @since 0.2.16
 */
vbi_bool
vbi_xds_demux_feed		(vbi_xds_demux *	xd,
				 const uint8_t		buffer[2])
{
	_vbi_xds_subpacket *sp;
	vbi_bool r;
	int c1, c2;

	assert (NULL != xd);
	assert (NULL != buffer);

	r = TRUE;

	sp = xd->curr_sp;

	LogMsg( LOG_INFO, "XDS demux %02x %02x\n", buffer[0], buffer[1] );

	c1 = vbi_unpar8 (buffer[0]);
	c2 = vbi_unpar8 (buffer[1]);

	if ((c1 | c2) < 0) {
		LogMsg( LOG_DEBUG, "XDS tx error, discard current packet\n" );
 
		if (sp) {
			sp->count = 0;
			sp->checksum = 0;
		}

		xd->curr_sp = NULL;

		return FALSE;
	}

	if ( ( 0x20 <= c1 )
		&& ( 0x7F >= c1 ) )
	{
		//case 0x20 ... 0x7F:
			/* Packet contents. */

		if ( !sp ) 
		{
			LogMsg( LOG_DEBUG, "XDS can't store packet, missed start\n" );
			return 0;
		}

		if ( sp->count >= sizeof( sp->buffer ) + 2 ) 
		{
			LogMsg( LOG_DEBUG,   "XDS discard packet 0x%x/0x%02x, "
				"buffer overflow\n",
				xd->curr.xds_class, xd->curr.xds_subclass );
			goto discard;
		}
	}
	else
	{
		switch ( c1 )
		{
		case 0x00:
			/* Stuffing. */

			break;

		case 0x01:
		case 0x02:
		case 0x03:
		case 0x04:
		case 0x05:
		case 0x06:
		case 0x07:
		case 0x08:
		case 0x09:
		case 0x0A:
		case 0x0B:
		case 0x0C:
		case 0x0D:
		case 0x0E:
		{
			vbi_xds_class xds_class;
			vbi_xds_subclass xds_subclass;
			unsigned int i;

			/* Packet header. */

			xds_class = ( c1 - 1 ) >> 1;
			xds_subclass = c2;

			i = xds_subclass;

			/* MISC subclass 0x4n */
			if ( i >= 0x40 )
				i += 0x10 - 0x40;

			if ( xds_class > VBI_XDS_CLASS_MISC
				|| i > N_ELEMENTS( xd->subpacket[ 0 ] ) ) {
				LogMsg( LOG_DEBUG,   "XDS ignore packet 0x%x/0x%02x, "
					"unknown class or subclass\n",
					xds_class, xds_subclass );
				goto discard;
			}

			sp = &xd->subpacket[ xds_class ][ i ];

			xd->curr_sp = sp;
			xd->curr.xds_class = xds_class;
			xd->curr.xds_subclass = xds_subclass;

			if ( c1 & 1 ) {
				/* Start packet. */
				sp->checksum = c1 + c2;
				sp->count = 2;
			}
			else {
				/* Continue packet. */
				if ( 0 == sp->count ) {
					LogMsg( LOG_DEBUG,   "XDS can't continue packet "
						"0x%x/0x%02x, missed start\n",
						xd->curr.xds_class,
						xd->curr.xds_subclass );
					goto discard;
				}
			}

			break;
		}

		case 0x0F:
			/* Packet terminator. */

			if ( !sp ) {
				LogMsg( LOG_DEBUG,   "XDS can't finish packet, missed start\n" );
				break;
			}

			sp->checksum += c1 + c2;

			if ( 0 != ( sp->checksum & 0x7F ) ) {
				LogMsg( LOG_DEBUG,   "XDS ignore packet 0x%x/0x%02x, "
					"checksum error\n",
					xd->curr.xds_class, xd->curr.xds_subclass );
			}
			else if ( sp->count <= 2 ) {
				LogMsg( LOG_DEBUG, "XDS ignore empty packet 0x%x/0x%02x\n",
					xd->curr.xds_class, xd->curr.xds_subclass );
			}
			else {
				memcpy( xd->curr.buffer, sp->buffer, 32 );

				xd->curr.buffer_size = sp->count - 2;
				xd->curr.buffer[ sp->count - 2 ] = 0;

				if ( XDS_DEMUX_LOG )
					_vbi_xds_packet_dump( &xd->curr, stderr );

				r = xd->callback( xd, &xd->curr, xd->user_data );
			}

			/* fall through */

		discard:
			if ( sp ) {
				sp->count = 0;
				sp->checksum = 0;
			}

			/* fall through */

		case 0x10:
		case 0x11:
		case 0x12:
		case 0x13:
		case 0x14:
		case 0x15:
		case 0x16:
		case 0x17:
		case 0x18:
		case 0x19:
		case 0x1A:
		case 0x1B:
		case 0x1C:
		case 0x1D:
		case 0x1E:
		case 0x1F:
			/* Closed Caption. */

			xd->curr_sp = NULL;
		default:
			break;
		}
	}

	return r;
}

/**
 * @param xd XDS demultiplexer context allocated with vbi_xds_demux_new().
 * @param sliced Sliced VBI data.
 * @param n_lines Number of lines in the @a sliced array.
 *
 * This function works like vbi_xds_demux_feed() but operates on sliced
 * VBI data and filters out @c VBI_SLICED_CAPTION_525 on NTSC line 284.
 *
 * @returns
 * @c FALSE if any of the Caption lines contained parity errors.
 *
 * @since 0.2.26
 */
vbi_bool
vbi_xds_demux_feed_frame	(vbi_xds_demux *	xd,
				 const vbi_sliced *	sliced,
				 unsigned int		n_lines)
{
	const vbi_sliced *end;

	assert (NULL != xd);
	assert (NULL != sliced);

	for (end = sliced + n_lines; sliced < end; ++sliced) {
		switch (sliced->id) {
		case VBI_SLICED_CAPTION_525:
		case VBI_SLICED_CAPTION_525_F2:
			if (284 != sliced->line
			    && 0 != sliced->line)
				continue;

			if (!vbi_xds_demux_feed (xd, sliced->data))
				return FALSE;

			break;

		default:
			break;
		}
	}

	return TRUE;
}

#if 0 /* ideas */
const vbi_xds_packet *
vbi_xds_demux_get_packet	(vbi_xds_demux *	xd,
				 vbi_xds_class		xds_class,
				 vbi_xds_subclass	xds_subclass)
{
	/* most recently received packet of this class. */
}

const vbi_xds_packet *
vbi_xds_demux_cor		(vbi_xds_demux *	xd,
				 const uint8_t		buffer[2])
{
	...
}

void
vbi_xds_demux_set_log		(vbi_xds_demux *	xd,
				 vbi_log_fn *		callback,
				 unsigned int		pri_mask)
{
	...
}
#endif

/** @internal */
void
_vbi_xds_demux_destroy		(vbi_xds_demux *	xd)
{
	assert (NULL != xd);

	CLEAR (*xd);
}

/** @internal */
vbi_bool
_vbi_xds_demux_init		(vbi_xds_demux *	xd,
				 vbi_xds_demux_cb *	callback,
				 void *			user_data)
{
	assert (NULL != xd);
	assert (NULL != callback);

	vbi_xds_demux_reset (xd);

	xd->callback = callback;
	xd->user_data = user_data;

	return TRUE;
}

/**
 * @param xd XDS demultiplexer context allocated with
 *   vbi_xds_demux_new(), can be @c NULL.
 *
 * Frees all resources associated with @a xd.
 *
 * @since 0.2.16
 */
void
vbi_xds_demux_delete		(vbi_xds_demux *	xd)
{
	if (NULL == xd)
		return;

	_vbi_xds_demux_destroy (xd);

	free (xd);		
}

/**
 * @param callback Function to be called by vbi_xds_demux_feed() when
 *   a new packet is available.
 * @param user_data User pointer passed through to @a callback function.
 *
 * Allocates a new Extended Data Service (EIA 608) demultiplexer.
 *
 * @returns
 * Pointer to newly allocated XDS demux context which must be
 * freed with vbi_xds_demux_delete() when done. @c NULL on failure
 * (out of memory).
 *
 * @since 0.2.16
 */
vbi_xds_demux *
vbi_xds_demux_new		(vbi_xds_demux_cb *	callback,
				 void *			user_data)
{
	vbi_xds_demux *xd;

	assert (NULL != callback);

	if (!(xd = malloc (sizeof (*xd)))) {
		return NULL;
	}

	_vbi_xds_demux_init (xd, callback, user_data);

	return xd;
}

/*
Local variables:
c-set-style: K&R
c-basic-offset: 8
End:
*/
