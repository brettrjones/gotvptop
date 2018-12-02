///////////////////////////////////////////////////////////////////////////////
//
/// \file       hardware_physmem.c
/// \brief      Get the total amount of physical memory (RAM)
//
//  Author:     Jonathan Nieder
//
//  This file has been put into the public domain.
//  You can do whatever you want with this file.
//
///////////////////////////////////////////////////////////////////////////////

#if 0 // BRJ TODO add physmem support?
#include <liblzma/common/common_lzma.h>

#include "tuklib_physmem.h"


extern LZMA_API(uint64_t)
lzma_physmem(void)
{
	// It is simpler to make lzma_physmem() a wrapper for
	// tuklib_physmem() than to hack appropriate symbol visiblity
	// support for the tuklib modules.
	return tuklib_physmem();
}

#endif // 0 