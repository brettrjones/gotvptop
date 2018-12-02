HEADERS += 	$$PWD/../../config_libcpluff.h \
	$$PWD/../../cpluff.h \
	$$PWD/../../cpluffdef_linux.h \
	$$PWD/../../cpluffdef_win32.h \
	$$PWD/../../defines.h \
	$$PWD/../../internal.h \
	$$PWD/../../kazlib/hash.h \
	$$PWD/../../kazlib/list.h \
	$$PWD/../../thread.h \
	$$PWD/../../util.h

SOURCES += 	$$PWD/../../context.c \
	$$PWD/../../cpluff.c \
	$$PWD/../../kazlib/hash.c \
	$$PWD/../../kazlib/list.c \
	$$PWD/../../loader/loader.c \
	$$PWD/../../logging.c \
	$$PWD/../../pcontrol.c \
	$$PWD/../../pinfo.c \
	$$PWD/../../ploader.c \
	$$PWD/../../pscan.c \
	$$PWD/../../psymbol.c \
	$$PWD/../../serial.c \
	$$PWD/../../thread_posix.c \
	$$PWD/../../thread_windows.c \
	$$PWD/../../util.c

