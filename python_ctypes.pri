HEADERS += 	$$PWD/../Modules/_ctypes/ctypes.h \
	$$PWD/../Modules/_ctypes/ctypes_dlfcn.h \
	$$PWD/../Modules/_ctypes/libffi_msvc/ffi.h \
	$$PWD/../Modules/_ctypes/libffi_msvc/ffi_common.h \
	$$PWD/../Modules/_ctypes/libffi_msvc/fficonfig.h \
	$$PWD/../Modules/_ctypes/libffi_msvc/ffitarget.h

SOURCES += 	$$PWD/../Modules/_ctypes/_ctypes.c \
	$$PWD/../Modules/_ctypes/callbacks.c \
	$$PWD/../Modules/_ctypes/callproc.c \
	$$PWD/../Modules/_ctypes/cfield.c \
	$$PWD/../Modules/_ctypes/libffi_msvc/ffi.c \
	$$PWD/../Modules/_ctypes/libffi_msvc/prep_cif.c \
	$$PWD/../Modules/_ctypes/libffi_msvc/win32.c \
	$$PWD/../Modules/_ctypes/malloc_closure.c \
	$$PWD/../Modules/_ctypes/stgdict.c

