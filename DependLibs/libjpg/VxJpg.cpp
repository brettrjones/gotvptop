
#include <stdio.h>
extern "C" { 
#include "jpeglib.h" 
}
#include <setjmp.h>
#include "VxJpgLib.h"
#include "stdlib.h"
#include "stdio.h"
#include "memory.h"

struct jpg_datastore{
  unsigned char *data;
  size_t len;

  jpg_datastore () { data = 0; len = 0; }
  ~jpg_datastore () { free (data); }
};


struct my_dst_mgr
{
  static size_t buf_len;
  struct jpeg_destination_mgr pub;	/* public fields */
  JOCTET *buffer;		/* start of buffer */

  jpg_datastore *ds;
};

size_t my_dst_mgr::buf_len = 4096;

static void init_destination (j_compress_ptr cinfo)
{
  my_dst_mgr *dest = (my_dst_mgr*)cinfo->dest;
  dest->buffer = (JOCTET*)(*cinfo->mem->alloc_small)((j_common_ptr)cinfo,
    JPOOL_IMAGE, sizeof(JOCTET) * my_dst_mgr::buf_len);
  dest->pub.next_output_byte = dest->buffer;
  dest->pub.free_in_buffer = my_dst_mgr::buf_len;
}

static boolean empty_output_buffer (j_compress_ptr cinfo)
{
  my_dst_mgr *dest = (my_dst_mgr*)cinfo->dest;

  dest->ds->data = (unsigned char*)realloc (dest->ds->data,
    dest->ds->len + sizeof(JOCTET) * my_dst_mgr::buf_len);
  if (!dest->ds->data)
	  return false;
    //ERREXITS(cinfo,-1, "Could not reallocate enough memory");
    //ERREXITS(cinfo,JERR_OUT_OF_MEMORY, "Could not reallocate enough memory");
  memcpy (dest->ds->data + dest->ds->len, dest->buffer,
    sizeof(JOCTET) * my_dst_mgr::buf_len);
  dest->pub.next_output_byte = dest->buffer;
  dest->pub.free_in_buffer = my_dst_mgr::buf_len;
  dest->ds->len += sizeof(JOCTET) * my_dst_mgr::buf_len;
  return true;
}


static void term_destination (j_compress_ptr cinfo)
{
  my_dst_mgr *dest = (my_dst_mgr*)cinfo->dest;
  size_t len = my_dst_mgr::buf_len - dest->pub.free_in_buffer;

  if (len > 0)
  {
    dest->ds->data = (unsigned char*)realloc (dest->ds->data,
      dest->ds->len + sizeof(JOCTET) * len);
    if (!dest->ds->data)
		return;
      //ERREXITS(cinfo,-1, "Could not reallocate enough memory");
      //ERREXITS(cinfo,JERR_OUT_OF_MEMORY, "Could not reallocate enough memory");
    memcpy(dest->ds->data + dest->ds->len, dest->buffer, sizeof(JOCTET) * len);
    dest->ds->len += sizeof(JOCTET) * len;
  }
}

static void jpeg_buffer_dest (j_compress_ptr cinfo, jpg_datastore *ds)
{
  my_dst_mgr *dest;

  if (cinfo->dest == 0)
    cinfo->dest = (struct jpeg_destination_mgr*)(*cinfo->mem->alloc_small)
      ((j_common_ptr)cinfo, JPOOL_PERMANENT, sizeof(my_dst_mgr));

  dest = (my_dst_mgr*)cinfo->dest;
  dest->pub.init_destination = init_destination;
  dest->pub.empty_output_buffer = empty_output_buffer;
  dest->pub.term_destination = term_destination;
  dest->ds = ds;
}

/*
static void jpeg_buffer_dest (j_compress_ptr cinfo, (char *)pu8RetJpg, int iJpgBufLen)
{
  my_dst_mgr *dest;

  if (cinfo->dest == 0)
    cinfo->dest = (struct jpeg_destination_mgr*)(*cinfo->mem->alloc_small)
      ((j_common_ptr)cinfo, JPOOL_PERMANENT, sizeof(my_dst_mgr));

  dest = (my_dst_mgr*)cinfo->dest;
  dest->pub.init_destination = init_destination;
  dest->pub.empty_output_buffer = empty_output_buffer;
  dest->pub.term_destination = term_destination;
  dest->ds = ds;
}
*/

/*
* IMAGE DATA FORMATS:
*
* The standard input image format is a rectangular array of pixels, with
* each pixel having the same number of "component" values (color channels).
* Each pixel row is an array of JSAMPLEs (which typically are unsigned chars).
* If you are working with color data, then the color values for each pixel
* must be adjacent in the row; for example, R,G,B,R,G,B,R,G,B,... for 24-bit
* RGB color.
*
* For this example, we'll assume that this data structure matches the way
* our application has stored the image in memory, so we can just pass a
* pointer to our image buffer.  In particular, let's say that the image is
* RGB color and is described by:
*/

RCODE VxBmp2Jpg(	int	iBitsPerPixel,		//number of bits each pixel..(For now must be 24)
					unsigned char * pu8Bits, //bits of bmp to convert
					int iWidth,		//width of image in pixels
					int iHeight,	//height of image in pixels
					int iQuality,	//quality of image
					int iJpgBufLen, //maximum length of pu8RetJpg
					unsigned char * pu8RetJpg, //buffer to return Jpeg image
					long * ps32RetJpgLen ) //return length of jpeg image
{
	
	* ps32RetJpgLen = 0;
	
/* This struct contains the JPEG compression parameters and pointers to
* working space (which is allocated as needed by the JPEG library).
* It is possible to have several such structures, representing multiple
* compression/decompression processes, in existence at once.  We refer
* to any one struct (and its associated working data) as a "JPEG object".
	*/
	struct jpeg_compress_struct cinfo;

	/* This struct represents a JPEG error handler.  It is declared separately
	* because applications often want to supply a specialized error handler
	* (see the second half of this file for an example).  But here we just
	* take the easy way out and use the standard error handler, which will
	* print a message on stderr and call exit() if compression fails.
	* Note that this struct must live as long as the main JPEG parameter
	* struct, to avoid dangling-pointer problems.
	*/
	struct jpeg_error_mgr jerr;
	/* More stuff */
//	FILE * outfile;		/* target file */
	
//	if ((outfile = fopen( "C:\\Test.jpg", "wb")) == NULL) {
//		fprintf(stderr, "can't open %s\n", "C:\\Test.jpg");
//		//   exit(1);
//		return 0;
//	}
	cinfo.err = jpeg_std_error(&jerr);
	/* Now we can initialize the JPEG compression object. */
	jpeg_create_compress(&cinfo);
	
	cinfo.in_color_space = JCS_RGB; /* arbitrary guess */
	jpeg_set_defaults(&cinfo );
	jpeg_default_colorspace(&cinfo);
	cinfo.in_color_space = JCS_RGB; 	/* colorspace of input image */
										/* Now use the library's routine to set default compression parameters.
										* (You must set at least cinfo.in_color_space before calling this,
										* since the defaults depend on the source color space.) */
	cinfo.image_width = iWidth; 	// image width and height, in pixels
	cinfo.image_height = iHeight;
	cinfo.input_components = 3;		/* # of color components per pixel */
	cinfo.data_precision = 8;
	cinfo.in_color_space = JCS_RGB; 	/* colorspace of input image */

	// Now use the library's routine to set default compression parameters.
	// (You must set at least cinfo.in_color_space before calling this,
	// since the defaults depend on the source color space.)
	jpeg_set_defaults(&cinfo);
  

//	VxJpg_stdio_dest(&cinfo, outfile );
//	jpeg_buffer_dest(&cinfo, (char *)pu8RetJpg, iJpgBufLen  );
	struct jpg_datastore ds;
	jpeg_buffer_dest(&cinfo, &ds );

	// Now you can set any non-default parameters you wish to.
	// Here we just illustrate the use of quality (quantization table) scaling:
	jpeg_set_quality(&cinfo, iQuality, TRUE /* limit to baseline-JPEG values */);
	
	/* Step 4: Start compressor */
	
	/* TRUE ensures that we will write a complete interchange-JPEG file.
	* Pass TRUE unless you are very sure of what you're doing.
	*/
	jpeg_start_compress(&cinfo, TRUE);
	#define ROUND_TO_4BYTE_BOUNDRY( a ) (( a + 3 ) & ~3 ) //round upto even 4 byte boundry
	
	int iLineByteCnt = ROUND_TO_4BYTE_BOUNDRY( iWidth*3 );
	
	// the scanlines go from bottom to top, but compressor wants then top to bottom
	while (cinfo.next_scanline < cinfo.image_height) 
	{
		/*
		//swap rgb to bgr
		for( int i = 0; i < iWidth; i++ )
		{
			int iIdx = i*3;
			unsigned char u8Color = pu8Bits[ iIdx ];
			pu8Bits[ iIdx ] = pu8Bits[ iIdx+2 ];
			pu8Bits[ iIdx + 2 ] = u8Color;
		}
		*/
		jpeg_write_scanlines(&cinfo, (unsigned char **)&pu8Bits, 1);
		pu8Bits += iLineByteCnt;
	}
	/*

	// the compressor writes it upside down so start from bottom to top
	pu8Bits = pu8Bits + (iLineByteCnt * ( cinfo.image_height - 1 ) );
	while( cinfo.next_scanline < iHeight ) 
	{
		//swap rgb to bgr
		unsigned char u8Color;
		int iIdx = 0;
		for( int i = 0; i < iWidth; i++ )
		{
			u8Color = pu8Bits[ iIdx ];
			pu8Bits[ iIdx ] = pu8Bits[ iIdx+2 ];
			pu8Bits[ iIdx + 2 ] = u8Color;
			iIdx += 3;
		}
		jpeg_write_scanlines(&cinfo, (unsigned char **)&pu8Bits, 1);
		pu8Bits -= iLineByteCnt;
	}
	*/

	
	jpeg_finish_compress(&cinfo);
	jpeg_destroy_compress(&cinfo);
	

	long s32Len = (long)ds.len;
	* ps32RetJpgLen = s32Len;
	memcpy( pu8RetJpg, ds.data, s32Len );

	return 0;
}


/*
* SOME FINE POINTS:
*
* In the above loop, we ignored the return value of jpeg_write_scanlines,
* which is the number of scanlines actually written.  We could get away
* with this because we were only relying on the value of cinfo.next_scanline,
* which will be incremented correctly.  If you maintain additional loop
* variables then you should be careful to increment them properly.
* Actually, for output to a stdio stream you needn't worry, because
* then jpeg_write_scanlines will write all the lines passed (or else exit
* with a fatal error).  Partial writes can only occur if you use a data
* destination module that can demand suspension of the compressor.
* (If you don't know what that's for, you don't need it.)
*
* If the compressor requires full-image buffers (for entropy-coding
* optimization or a multi-scan JPEG file), it will create temporary
* files for anything that doesn't fit within the maximum-memory setting.
* (Note that temp files are NOT needed if you use the default parameters.)
* On some systems you may need to set up a signal handler to ensure that
* temporary files are deleted if the program is interrupted.  See libjpeg.doc.
*
* Scanlines MUST be supplied in top-to-bottom order if you want your JPEG
* files to be compatible with everyone else's.  If you cannot readily read
* your data in that order, you'll need an intermediate array to hold the
* image.  See rdtarga.c or rdbmp.c for examples of handling bottom-to-top
* source data using the JPEG code's internal virtual-array mechanisms.
*/



/******************** JPEG DECOMPRESSION SAMPLE INTERFACE *******************/

/* This half of the example shows how to read data from the JPEG decompressor.
* It's a bit more refined than the above, in that we show:
*   (a) how to modify the JPEG library's standard error-reporting behavior;
*   (b) how to allocate workspace using the library's memory manager.
*
* Just to make this example a little different from the first one, we'll
* assume that we do not intend to put the whole image into an in-memory
* buffer, but to send it line-by-line someplace else.  We need a one-
* scanline-high JSAMPLE array as a work buffer, and we will let the JPEG
* memory manager allocate it for us.  This approach is actually quite useful
* because we don't need to remember to deallocate the buffer separately: it
* will go away automatically when the JPEG object is cleaned up.
*/


/*
* ERROR HANDLING:
*
* The JPEG library's standard errnor handler (jerror.c) is divided into
* several "methods" which you can override individually.  This lets you
* adjust the behavior without duplicating a lot of code, which you might
* have to update with each future release.
*
* Our example here shows how to override the "error_exit" method so that
* control is returned to the library's caller when a fatal error occurs,
* rather than calling exit() as the standard error_exit method does.
*
* We use C's setjmp/longjmp facility to return control.  This means that the
* routine which calls the JPEG library must first execute a setjmp() call to
* establish the return point.  We want the replacement error_exit to do a
* longjmp().  But we need to make the setjmp buffer accessible to the
* error_exit routine.  To do this, we make a private extension of the
* standard JPEG error handler object.  (If we were using C++, we'd say we
* were making a subclass of the regular error handler.)
*
* Here's the extended error handler struct:
*/

struct my_error_mgr {
	struct jpeg_error_mgr pub;	/* "public" fields */
	
	jmp_buf setjmp_buffer;	/* for return to caller */
};
struct my_jpeg_source_mgr : public jpeg_source_mgr
{
//  const JOCTET * next_input_byte;		/* => next byte to read from buffer */
//  size_t bytes_in_buffer;				/* # of bytes remaining in buffer */
  const JOCTET * orig_next_input_byte;	/* => next byte to read from buffer */
  size_t orig_bytes_in_buffer;			/* # of bytes in original buffer */
  size_t iBufOffs;			/* # of bytes in original buffer */

//  JMETHOD(void, init_source, (j_decompress_ptr cinfo));
//  JMETHOD(boolean, fill_input_buffer, (j_decompress_ptr cinfo));
//  JMETHOD(void, skip_input_data, (j_decompress_ptr cinfo, long num_bytes));
//  JMETHOD(boolean, resync_to_restart, (j_decompress_ptr cinfo, int desired));
//  JMETHOD(void, term_source, (j_decompress_ptr cinfo));
};

typedef struct my_error_mgr * my_error_ptr;

/*
* Here's the routine that will replace the standard error_exit method:
*/

METHODDEF(void)
my_error_exit (j_common_ptr cinfo)
{
	/* cinfo->err really points to a my_error_mgr struct, so coerce pointer */
	my_error_ptr myerr = (my_error_ptr) cinfo->err;
	
	/* Always display the message. */
	/* We could postpone this until after returning, if we chose. */
	(*cinfo->err->output_message) (cinfo);
	
	/* Return control to the setjmp point */
	longjmp(myerr->setjmp_buffer, 1);
}


RCODE VxWriteJpg(	const char *    pFileName,
                    int             iBitsPerPixel,		//number of bits each pixel..(For now must be 24)
                    unsigned char * pu8Bits, //bits of bmp to convert
                    int             iWidth,		//width of image in pixels
                    int             iHeight,	//height of image in pixels
                    int             iQuality )	//quality of image
{
	FILE * pgFile;
	if( NULL == ( pgFile = fopen( pFileName, "wb") ) ) 
	{
		return -1;
	}
	
	int iJpgBufLen = (((iBitsPerPixel / 8) * iWidth) * iHeight) + 100;
	unsigned char * pu8Jpg = new unsigned char[ iJpgBufLen ];
	long s32JpgLen = 0; //length of jpeg image
	
	RCODE rc = VxBmp2Jpg(	iBitsPerPixel,	//number of bits each pixel..(For now must be 24)
							pu8Bits,		//bits of bmp to convert
							iWidth,			//width of image in pixels
							iHeight,		//height of image in pixels
							iQuality,		//quality of image
							iJpgBufLen,		//maximum length of pu8RetJpg
							pu8Jpg,			//buffer to return Jpeg image
							&s32JpgLen );	//return length of jpeg image
	if( 0 == rc )
	{
		if( s32JpgLen != fwrite( pu8Jpg, 1, s32JpgLen, pgFile ) )
		{
			rc = -1;
		}
	}
	else
	{
		//		TRACE( "VxWriteJpg Error %d\n", rc );
	}

	fclose( pgFile );
	delete[] pu8Jpg;
	return rc;
}

extern "C" 
{

LOCAL(void) my_init_source(j_decompress_ptr cinfo) 
{
}

LOCAL(boolean) my_fill_input_buffer(j_decompress_ptr cinfo)
{
	return true;
}

LOCAL(void) my_skip_input_data(j_decompress_ptr cinfo, long num_bytes)
{
	my_jpeg_source_mgr * poMgr = (my_jpeg_source_mgr *)cinfo->src;
	poMgr->iBufOffs += num_bytes;
	poMgr->next_input_byte = &poMgr->orig_next_input_byte[poMgr->iBufOffs];
	poMgr->bytes_in_buffer -= num_bytes;
}
LOCAL(boolean)
my_jpeg_resync_to_restart(j_decompress_ptr cinfo, int desired)
{
	my_jpeg_source_mgr * poMgr = (my_jpeg_source_mgr *)cinfo->src;
	poMgr->next_input_byte = poMgr->orig_next_input_byte;
	poMgr->bytes_in_buffer = poMgr->orig_bytes_in_buffer;
	return true;
};
LOCAL(void)
my_term_source(j_decompress_ptr cinfo)
{
}
}

RCODE VxJpg2Bmp(	unsigned char * pu8Bits,		// bits of jpg to convert
					unsigned long	u32DataLen,		// length of jpg data
					int				iWidth,			// width of image in pixels
					int				iHeight,		// height of image in pixels
					unsigned char * pu8RetBmp,		// buffer to return Bmp Data
					long *			ps32RetBmpLen ) //return length of Bmp data
{
	
	* ps32RetBmpLen = 0;
	unsigned char **rowPtr=0;
	unsigned char * input = pu8Bits;
	JSAMPARRAY buffer;		/* Output row buffer */
	int row_stride;				/* physical row width in output buffer */
	int iRetBufIdx = 0;

	// allocate and initialize JPEG decompression object
	struct jpeg_decompress_struct cinfo;
	struct my_error_mgr jerr;

	//We have to set up the error handler first, in case the initialization
	//step fails.  (Unlikely, but it could happen if you are out of memory.)
	//This routine fills in the contents of struct jerr, and returns jerr's
	//address which we place into the link field in cinfo.

	cinfo.err = jpeg_std_error(&jerr.pub);
	cinfo.err->error_exit = my_error_exit;
	
	// compatibility fudge:
	// we need to use setjmp/longjmp for error handling as gcc-linux
	// crashes when throwing within external c code
	if (setjmp(jerr.setjmp_buffer))
	{
		// If we get here, the JPEG code has signaled an error.
		// We need to clean up the JPEG object and return.

		jpeg_destroy_decompress(&cinfo);

		delete [] input;
		// if the row pointer was created, we delete it.
		if (rowPtr)
			delete [] rowPtr;

		// return null pointer
		return 0;
	}

	/* Now we can initialize the JPEG decompression object. */
	jpeg_create_decompress(&cinfo);

	/* Step 2: specify data source (eg, a file) */

	// specify data source
	my_jpeg_source_mgr jsrc;

	// Set up data pointer
	jsrc.bytes_in_buffer = u32DataLen;
	jsrc.next_input_byte = (JOCTET*)input;
	jsrc.orig_bytes_in_buffer = u32DataLen;
	jsrc.orig_next_input_byte = (JOCTET*)input;
	jsrc.iBufOffs = 0;
	cinfo.src = (jpeg_source_mgr *)&jsrc;

	jsrc.init_source		= my_init_source;
	jsrc.fill_input_buffer	= my_fill_input_buffer;
	jsrc.skip_input_data	= my_skip_input_data;
	jsrc.resync_to_restart	= my_jpeg_resync_to_restart;
	jsrc.term_source		= my_term_source;

	/* Step 3: read file parameters with jpeg_read_header() */

	(void) jpeg_read_header(&cinfo, TRUE);
	/* We can ignore the return value from jpeg_read_header since
	*   (a) suspension is not possible with the stdio data source, and
	*   (b) we passed TRUE to reject a tables-only JPEG file as an error.
	* See libjpeg.doc for more info.
	*/

	/* Step 4: set parameters for decompression */

	/* In this example, we don't need to change any of the defaults set by
	* jpeg_read_header(), so we do nothing here.
	*/

	/* Step 5: Start decompressor */

	(void) jpeg_start_decompress(&cinfo);
	/* We can ignore the return value since suspension is not possible
	* with the stdio data source.
	*/

	/* We may need to do some setup of our own at this point before reading
	* the data.  After jpeg_start_decompress() we have the correct scaled
	* output image dimensions available, as well as the output colormap
	* if we asked for color quantization.
	* In this example, we need to make an output work buffer of the right size.
	*/ 
	/* JSAMPLEs per row in output buffer */
	row_stride = cinfo.output_width * cinfo.output_components;
	/* Make a one-row-high sample array that will go away when done with image */
	buffer = (*cinfo.mem->alloc_sarray)
		((j_common_ptr) &cinfo, JPOOL_IMAGE, row_stride, 1);

	/* Step 6: while (scan lines remain to be read) */
	/*           jpeg_read_scanlines(...); */

	/* Here we use the library's state variable cinfo.output_scanline as the
	* loop counter, so that we don't have to keep track ourselves.
	*/
	while (cinfo.output_scanline < cinfo.output_height) {
		/* jpeg_read_scanlines expects an array of pointers to scanlines.
		 * Here the array is only one element long, but you could ask for
		 * more than one scanline at a time if that's more convenient.
		 */
		(void) jpeg_read_scanlines(&cinfo, buffer, 1);
		/* Assume put_scanline_someplace wants a pointer and sample count. */
		//put_scanline_someplace(buffer[0], row_stride);
		memcpy( &pu8RetBmp[iRetBufIdx], buffer[0], row_stride);
		iRetBufIdx += row_stride;

	}

	/* Step 7: Finish decompression */

	(void) jpeg_finish_decompress(&cinfo);
	/* We can ignore the return value since suspension is not possible
	* with the stdio data source.
	*/

	/* Step 8: Release JPEG decompression object */

	/* This is an important step since it will release a good deal of memory. */
	jpeg_destroy_decompress(&cinfo);

	/* After finish_decompress, we can close the input file.
	* Here we postpone it until after no more JPEG errors are possible,
	* so as to simplify the setjmp error logic above.  (Actually, I don't
	* think that jpeg_destroy can do an error exit, but why assume anything...)
	*/
	//fclose(infile);

	/* At this point you may want to check to see whether any corrupt-data
	* warnings occurred (test whether jerr.pub.num_warnings is nonzero).
	*/

	/* And we're done! */
	return 0;
}
