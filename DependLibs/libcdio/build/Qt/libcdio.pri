
INCLUDEPATH += 	$$PWD/../../
INCLUDEPATH += 	$$PWD/../../lib/iso9660
INCLUDEPATH += 	$$PWD/../../lib/driver

HEADERS += 	$$PWD/../../include/cdio/audio.h \
	$$PWD/../../include/cdio/bytesex.h \
	$$PWD/../../include/cdio/bytesex_asm.h \
	$$PWD/../../include/cdio/cd_types.h \
	$$PWD/../../include/cdio/cdio.h \
	$$PWD/../../include/cdio/cdtext.h \
	$$PWD/../../include/cdio/device.h \
	$$PWD/../../include/cdio/disc.h \
	$$PWD/../../include/cdio/ds.h \
	$$PWD/../../include/cdio/dvd.h \
	$$PWD/../../include/cdio/ecma_167.h \
	$$PWD/../../include/cdio/iso9660.h \
	$$PWD/../../include/cdio/logging.h \
	$$PWD/../../include/cdio/memory.h \
	$$PWD/../../include/cdio/mmc.h \
	$$PWD/../../include/cdio/mmc_cmds.h \
	$$PWD/../../include/cdio/mmc_hl_cmds.h \
	$$PWD/../../include/cdio/mmc_ll_cmds.h \
	$$PWD/../../include/cdio/mmc_util.h \
	$$PWD/../../include/cdio/posix.h \
	$$PWD/../../include/cdio/read.h \
	$$PWD/../../include/cdio/rock.h \
	$$PWD/../../include/cdio/scsi_mmc.h \
	$$PWD/../../include/cdio/sector.h \
	$$PWD/../../include/cdio/track.h \
	$$PWD/../../include/cdio/types.h \
	$$PWD/../../include/cdio/udf.h \
	$$PWD/../../include/cdio/udf_file.h \
	$$PWD/../../include/cdio/udf_time.h \
	$$PWD/../../include/cdio/utf8.h \
	$$PWD/../../include/cdio/util.h \
	$$PWD/../../include/cdio/xa.h \
	$$PWD/../../lib/driver/FreeBSD/freebsd.h \
	$$PWD/../../lib/driver/MSWindows/aspi32.h \
	$$PWD/../../lib/driver/MSWindows/win32.h \
	$$PWD/../../lib/driver/_cdio_stdio.h \
	$$PWD/../../lib/driver/_cdio_stream.h \
	$$PWD/../../lib/driver/cdio_assert.h \
	$$PWD/../../lib/driver/cdio_private.h \
	$$PWD/../../lib/driver/cdtext_private.h \
	$$PWD/../../lib/driver/filemode.h \
	$$PWD/../../lib/driver/generic.h \
	$$PWD/../../lib/driver/image.h \
	$$PWD/../../lib/driver/image/nrg.h \
	$$PWD/../../lib/driver/image_common.h \
	$$PWD/../../lib/driver/mmc/mmc_cmd_helper.h \
	$$PWD/../../lib/driver/mmc/mmc_private.h \
	$$PWD/../../lib/driver/portable.h \
	$$PWD/../../lib/iso9660/iso9660_private.h \
	$$PWD/../../lib/udf/udf_fs.h \
	$$PWD/../../lib/udf/udf_private.h

SOURCES += 	$$PWD/../../lib/cdio++/cdio.cpp \
	$$PWD/../../lib/cdio++/devices.cpp \
	$$PWD/../../lib/cdio++/iso9660_cdio.cpp \
	$$PWD/../../lib/driver/FreeBSD/freebsd.c \
	$$PWD/../../lib/driver/FreeBSD/freebsd_cam.c \
	$$PWD/../../lib/driver/FreeBSD/freebsd_ioctl.c \
	$$PWD/../../lib/driver/MSWindows/aspi32.c \
	$$PWD/../../lib/driver/MSWindows/win32.c \
	$$PWD/../../lib/driver/MSWindows/win32_ioctl.c \
	$$PWD/../../lib/driver/_cdio_generic.c \
	$$PWD/../../lib/driver/_cdio_stdio.c \
	$$PWD/../../lib/driver/_cdio_stream.c \
	$$PWD/../../lib/driver/abs_path.c \
	$$PWD/../../lib/driver/aix.c \
	$$PWD/../../lib/driver/audio.c \
	$$PWD/../../lib/driver/bsdi.c \
	$$PWD/../../lib/driver/cd_types.c \
	$$PWD/../../lib/driver/cdtext.c \
	$$PWD/../../lib/driver/device.c \
	$$PWD/../../lib/driver/disc.c \
	$$PWD/../../lib/driver/ds.c \
	$$PWD/../../lib/driver/gnu_linux.c \
	$$PWD/../../lib/driver/image/bincue.c \
	$$PWD/../../lib/driver/image/cdrdao.c \
	$$PWD/../../lib/driver/image/nrg.c \
	$$PWD/../../lib/driver/image_common.c \
	$$PWD/../../lib/driver/logging.c \
	$$PWD/../../lib/driver/memory.c \
	$$PWD/../../lib/driver/mmc/mmc.c \
	$$PWD/../../lib/driver/mmc/mmc_hl_cmds.c \
	$$PWD/../../lib/driver/mmc/mmc_ll_cmds.c \
	$$PWD/../../lib/driver/mmc/mmc_util.c \
	$$PWD/../../lib/driver/netbsd.c \
	$$PWD/../../lib/driver/os2.c \
	$$PWD/../../lib/driver/osx.c \
	$$PWD/../../lib/driver/read.c \
	$$PWD/../../lib/driver/realpath.c \
	$$PWD/../../lib/driver/sector.c \
	$$PWD/../../lib/driver/solaris.c \
	$$PWD/../../lib/driver/track.c \
	$$PWD/../../lib/driver/utf8.c \
	$$PWD/../../lib/driver/util.c \
	$$PWD/../../lib/iso9660/iso9660.c \
	$$PWD/../../lib/iso9660/iso9660_fs.c \
	$$PWD/../../lib/iso9660/rock.c \
	$$PWD/../../lib/iso9660/xa.c \
	$$PWD/../../lib/udf/filemode.c \
	$$PWD/../../lib/udf/udf.c \
	$$PWD/../../lib/udf/udf_file.c \
	$$PWD/../../lib/udf/udf_fs.c \
	$$PWD/../../lib/udf/udf_time.c

