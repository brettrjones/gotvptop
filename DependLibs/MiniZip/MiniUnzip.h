/*
   miniunz.c
   Version 1.1, February 14h, 2010
   sample part of the MiniZip project - ( http://www.winimage.com/zLibDll/minizip.html )

         Copyright (C) 1998-2010 Gilles Vollant (minizip) ( http://www.winimage.com/zLibDll/minizip.html )

         Modifications of Unzip for Zip64
         Copyright (C) 2007-2008 Even Rouault

         Modifications for Zip64 support on both zip and unzip
         Copyright (C) 2009-2010 Mathias Svensson ( http://result42.com )
*/

#ifdef __cplusplus
extern "C" {
#endif


void	Unzip_ResetOptions( void );
void	Unzip_SetDirectoryToExtractTo( const char * dir );
void	Unzip_SetZipFileName( const char * fileName );
int		Unzip_ExecuteExtraction( void );

#ifdef __cplusplus
}
#endif

