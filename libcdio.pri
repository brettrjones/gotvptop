
INCLUDEPATH += 	$$PWD/DependLibs/libcdio/
INCLUDEPATH += 	$$PWD/DependLibs/libcdio/lib/iso9660
INCLUDEPATH += 	$$PWD/DependLibs/libcdio/lib/driver

HEADERS += 	$$PWD/DependLibs/libcdio/include/cdio/audio.h \
    $$PWD/DependLibs/libcdio/include/cdio/bytesex.h \
    $$PWD/DependLibs/libcdio/include/cdio/bytesex_asm.h \
    $$PWD/DependLibs/libcdio/include/cdio/cd_types.h \
    $$PWD/DependLibs/libcdio/include/cdio/cdio.h \
    $$PWD/DependLibs/libcdio/include/cdio/cdtext.h \
    $$PWD/DependLibs/libcdio/include/cdio/device.h \
    $$PWD/DependLibs/libcdio/include/cdio/disc.h \
    $$PWD/DependLibs/libcdio/include/cdio/ds.h \
    $$PWD/DependLibs/libcdio/include/cdio/dvd.h \
    $$PWD/DependLibs/libcdio/include/cdio/ecma_167.h \
    $$PWD/DependLibs/libcdio/include/cdio/iso9660.h \
    $$PWD/DependLibs/libcdio/include/cdio/logging.h \
    $$PWD/DependLibs/libcdio/include/cdio/memory.h \
    $$PWD/DependLibs/libcdio/include/cdio/mmc.h \
    $$PWD/DependLibs/libcdio/include/cdio/mmc_cmds.h \
    $$PWD/DependLibs/libcdio/include/cdio/mmc_hl_cmds.h \
    $$PWD/DependLibs/libcdio/include/cdio/mmc_ll_cmds.h \
    $$PWD/DependLibs/libcdio/include/cdio/mmc_util.h \
    $$PWD/DependLibs/libcdio/include/cdio/posix.h \
    $$PWD/DependLibs/libcdio/include/cdio/read.h \
    $$PWD/DependLibs/libcdio/include/cdio/rock.h \
    $$PWD/DependLibs/libcdio/include/cdio/scsi_mmc.h \
    $$PWD/DependLibs/libcdio/include/cdio/sector.h \
    $$PWD/DependLibs/libcdio/include/cdio/track.h \
    $$PWD/DependLibs/libcdio/include/cdio/types.h \
    $$PWD/DependLibs/libcdio/include/cdio/udf.h \
    $$PWD/DependLibs/libcdio/include/cdio/udf_file.h \
    $$PWD/DependLibs/libcdio/include/cdio/udf_time.h \
    $$PWD/DependLibs/libcdio/include/cdio/utf8.h \
    $$PWD/DependLibs/libcdio/include/cdio/util.h \
    $$PWD/DependLibs/libcdio/include/cdio/xa.h \
    $$PWD/DependLibs/libcdio/lib/driver/FreeBSD/freebsd.h \
    $$PWD/DependLibs/libcdio/lib/driver/MSWindows/aspi32.h \
    $$PWD/DependLibs/libcdio/lib/driver/MSWindows/win32.h \
    $$PWD/DependLibs/libcdio/lib/driver/_cdio_stdio.h \
    $$PWD/DependLibs/libcdio/lib/driver/_cdio_stream.h \
    $$PWD/DependLibs/libcdio/lib/driver/cdio_assert.h \
    $$PWD/DependLibs/libcdio/lib/driver/cdio_private.h \
    $$PWD/DependLibs/libcdio/lib/driver/cdtext_private.h \
    $$PWD/DependLibs/libcdio/lib/driver/filemode.h \
    $$PWD/DependLibs/libcdio/lib/driver/generic.h \
    $$PWD/DependLibs/libcdio/lib/driver/image.h \
    $$PWD/DependLibs/libcdio/lib/driver/image/nrg.h \
    $$PWD/DependLibs/libcdio/lib/driver/image_common.h \
    $$PWD/DependLibs/libcdio/lib/driver/mmc/mmc_cmd_helper.h \
    $$PWD/DependLibs/libcdio/lib/driver/mmc/mmc_private.h \
    $$PWD/DependLibs/libcdio/lib/driver/portable.h \
    $$PWD/DependLibs/libcdio/lib/iso9660/iso9660_private.h \
    $$PWD/DependLibs/libcdio/lib/udf/udf_fs.h \
    $$PWD/DependLibs/libcdio/lib/udf/udf_private.h

SOURCES += 	$$PWD/DependLibs/libcdio/lib/cdio++/cdio.cpp \
    $$PWD/DependLibs/libcdio/lib/cdio++/devices.cpp \
    $$PWD/DependLibs/libcdio/lib/cdio++/iso9660_cdio.cpp \
    $$PWD/DependLibs/libcdio/lib/driver/FreeBSD/freebsd.c \
    $$PWD/DependLibs/libcdio/lib/driver/FreeBSD/freebsd_cam.c \
    $$PWD/DependLibs/libcdio/lib/driver/FreeBSD/freebsd_ioctl.c \
    $$PWD/DependLibs/libcdio/lib/driver/MSWindows/aspi32.c \
    $$PWD/DependLibs/libcdio/lib/driver/MSWindows/win32.c \
    $$PWD/DependLibs/libcdio/lib/driver/MSWindows/win32_ioctl.c \
    $$PWD/DependLibs/libcdio/lib/driver/_cdio_generic.c \
    $$PWD/DependLibs/libcdio/lib/driver/_cdio_stdio.c \
    $$PWD/DependLibs/libcdio/lib/driver/_cdio_stream.c \
    $$PWD/DependLibs/libcdio/lib/driver/abs_path.c \
    $$PWD/DependLibs/libcdio/lib/driver/aix.c \
    $$PWD/DependLibs/libcdio/lib/driver/audio.c \
    $$PWD/DependLibs/libcdio/lib/driver/bsdi.c \
    $$PWD/DependLibs/libcdio/lib/driver/cd_types.c \
    $$PWD/DependLibs/libcdio/lib/driver/cdtext.c \
    $$PWD/DependLibs/libcdio/lib/driver/device.c \
    $$PWD/DependLibs/libcdio/lib/driver/disc.c \
    $$PWD/DependLibs/libcdio/lib/driver/ds.c \
    $$PWD/DependLibs/libcdio/lib/driver/gnu_linux.c \
    $$PWD/DependLibs/libcdio/lib/driver/image/bincue.c \
    $$PWD/DependLibs/libcdio/lib/driver/image/cdrdao.c \
    $$PWD/DependLibs/libcdio/lib/driver/image/nrg.c \
    $$PWD/DependLibs/libcdio/lib/driver/image_common.c \
    $$PWD/DependLibs/libcdio/lib/driver/logging.c \
    $$PWD/DependLibs/libcdio/lib/driver/memory.c \
    $$PWD/DependLibs/libcdio/lib/driver/mmc/mmc.c \
    $$PWD/DependLibs/libcdio/lib/driver/mmc/mmc_hl_cmds.c \
    $$PWD/DependLibs/libcdio/lib/driver/mmc/mmc_ll_cmds.c \
    $$PWD/DependLibs/libcdio/lib/driver/mmc/mmc_util.c \
    $$PWD/DependLibs/libcdio/lib/driver/netbsd.c \
    $$PWD/DependLibs/libcdio/lib/driver/os2.c \
    $$PWD/DependLibs/libcdio/lib/driver/osx.c \
    $$PWD/DependLibs/libcdio/lib/driver/read.c \
    $$PWD/DependLibs/libcdio/lib/driver/realpath.c \
    $$PWD/DependLibs/libcdio/lib/driver/sector.c \
    $$PWD/DependLibs/libcdio/lib/driver/solaris.c \
    $$PWD/DependLibs/libcdio/lib/driver/track.c \
    $$PWD/DependLibs/libcdio/lib/driver/utf8.c \
    $$PWD/DependLibs/libcdio/lib/driver/util.c \
    $$PWD/DependLibs/libcdio/lib/iso9660/iso9660.c \
    $$PWD/DependLibs/libcdio/lib/iso9660/iso9660_fs.c \
    $$PWD/DependLibs/libcdio/lib/iso9660/rock.c \
    $$PWD/DependLibs/libcdio/lib/iso9660/xa.c \
    $$PWD/DependLibs/libcdio/lib/udf/filemode.c \
    $$PWD/DependLibs/libcdio/lib/udf/udf.c \
    $$PWD/DependLibs/libcdio/lib/udf/udf_file.c \
    $$PWD/DependLibs/libcdio/lib/udf/udf_fs.c \
    $$PWD/DependLibs/libcdio/lib/udf/udf_time.c

