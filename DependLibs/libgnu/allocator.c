#define _GL_USE_STDLIB_ALLOC 1
#include <config_libgnu.h>
#include <stdlib.h>
#include "allocator.h"
#include <stdlib_gnu.h>
struct allocator const stdlib_allocator = { malloc, realloc, free, NULL };
