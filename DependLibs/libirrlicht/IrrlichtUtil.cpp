#include "irrlicht.h"
#include "VxUtilLib/VxUtilLib.h"
//! Dump matrix to log 
void DbgDumpMatrix( irr::core::matrix4& mat4 )
{
	log_msg( 0, "Dumping matrix4\n" );
	log_msg( 0, "mat4 Row 1 %3.2f, %3.2f, %3.2f, %3.2f\n", mat4.M[0],mat4.M[1],mat4.M[2], mat4.M[3] );
	log_msg( 0, "mat4 Row 2 %3.2f, %3.2f, %3.2f, %3.2f\n", mat4.M[4],mat4.M[5],mat4.M[6], mat4.M[7] );
	log_msg( 0, "mat4 Row 3 %3.2f, %3.2f, %3.2f, %3.2f\n", mat4.M[8],mat4.M[9],mat4.M[10], mat4.M[11] );
	log_msg( 0, "mat4 Row 4 %3.2f, %3.2f, %3.2f, %3.2f\n", mat4.M[12],mat4.M[13],mat4.M[14], mat4.M[15] );

}
