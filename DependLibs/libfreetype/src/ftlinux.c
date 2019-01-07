#include <libfreetype/include/ft2build.h>

#include FT_INTERNAL_DEBUG_H


#if defined(TARGET_OS_LINUX) || defined(TARGET_OS_ANDROID)
// linux
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>


  /* documentation is in ftdebug.h */

  FT_BASE_DEF( void )
  FT_Message( const char*  fmt,
              ... )
  {
    static char  buf[8192];
    va_list      ap;


    va_start( ap, fmt );
    vfprintf( stderr, fmt, ap );
    /* send the string to the debugger as well */
    vsprintf( buf, fmt, ap );
    printf( buf );
    va_end( ap );
  }


  /* documentation is in ftdebug.h */

  FT_BASE_DEF( void )
  FT_Panic( const char*  fmt,
            ... )
  {
    static char  buf[8192];
    va_list      ap;


    va_start( ap, fmt );
    vsprintf( buf, fmt, ap );
    printf( buf );
    va_end( ap );

    exit( EXIT_FAILURE );
  }


  /* documentation is in ftdebug.h */

  FT_BASE_DEF( int )
  FT_Throw( FT_Error     error,
            int          line,
            const char*  file )
  {
    FT_UNUSED( error );
    FT_UNUSED( line );
    FT_UNUSED( file );

    return 0;
  }


#ifdef FT_DEBUG_LEVEL_TRACE


  /* array of trace levels, initialized to 0 */
  int  ft_trace_levels[trace_count];

  /* define array of trace toggle names */
#define FT_TRACE_DEF( x )  #x ,

  static const char*  ft_trace_toggles[trace_count + 1] =
  {
#include FT_INTERNAL_TRACE_H
    NULL
  };

#undef FT_TRACE_DEF


  /*************************************************************************/
  /*                                                                       */
  /* Initialize the tracing sub-system.  This is done by retrieving the    */
  /* value of the "FT2_DEBUG" environment variable.  It must be a list of  */
  /* toggles, separated by spaces, `;' or `,'.  Example:                   */
  /*                                                                       */
  /*    "any:3 memory:6 stream:5"                                          */
  /*                                                                       */
  /* This will request that all levels be set to 3, except the trace level */
  /* for the memory and stream components which are set to 6 and 5,        */
  /* respectively.                                                         */
  /*                                                                       */
  /* See the file `include/freetype/internal/fttrace.h' for details of the */
  /* available toggle names.                                               */
  /*                                                                       */
  /* The level must be between 0 and 6; 0 means quiet (except for serious  */
  /* runtime errors), and 6 means _very_ verbose.                          */
  /*                                                                       */
  FT_BASE_DEF( void )
  ft_debug_init( void )
  {
    const char*  ft2_debug = getenv( "FT2_DEBUG" );


    if ( ft2_debug )
    {
      const char*  p = ft2_debug;
      const char*  q;


      for ( ; *p; p++ )
      {
        /* skip leading whitespace and separators */
        if ( *p == ' ' || *p == '\t' || *p == ',' || *p == ';' || *p == '=' )
          continue;

        /* read toggle name, followed by ':' */
        q = p;
        while ( *p && *p != ':' )
          p++;

        if ( !*p )
          break;

        if ( *p == ':' && p > q )
        {
          int  n, i, len = (int)( p - q );
          int  level = -1, found = -1;


          for ( n = 0; n < trace_count; n++ )
          {
            const char*  toggle = ft_trace_toggles[n];


            for ( i = 0; i < len; i++ )
            {
              if ( toggle[i] != q[i] )
                break;
            }

            if ( i == len && toggle[i] == 0 )
            {
              found = n;
              break;
            }
          }

          /* read level */
          p++;
          if ( *p )
          {
            level = *p - '0';
            if ( level < 0 || level > 7 )
              level = -1;
          }

          if ( found >= 0 && level >= 0 )
          {
            if ( found == trace_any )
            {
              /* special case for "any" */
              for ( n = 0; n < trace_count; n++ )
                ft_trace_levels[n] = level;
            }
            else
              ft_trace_levels[found] = level;
          }
        }
      }
    }
}

# endif // FT_DEBUG_LEVEL_TRACE
#endif // TARGET_OS_LINUX

/* END */

