
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

SOURCES += 	\
    $$PWD/DependLibs/libcdio/lib/cdio++/iso9660_cdio.cpp \
    $$PWD/DependLibs/libcdio/lib/cdio++/cdio_cdio.cpp \
    $$PWD/DependLibs/libcdio/lib/cdio++/devices_cdio.cpp \
    $$PWD/DependLibs/libcdio/lib/driver/FreeBSD/freebsd_cdio.c \
    $$PWD/DependLibs/libcdio/lib/driver/FreeBSD/freebsd_cam_cdio.c \
    $$PWD/DependLibs/libcdio/lib/driver/FreeBSD/freebsd_ioctl_cdio.c \
    $$PWD/DependLibs/libcdio/lib/driver/image/bincue_cdio.c \
    $$PWD/DependLibs/libcdio/lib/driver/image/cdrdao_cdio.c \
    $$PWD/DependLibs/libcdio/lib/driver/image/nrg_cdio.c \
    $$PWD/DependLibs/libcdio/lib/driver/mmc/mmc_cdio.c \
    $$PWD/DependLibs/libcdio/lib/driver/mmc/mmc_hl_cmds_cdio.c \
    $$PWD/DependLibs/libcdio/lib/driver/mmc/mmc_ll_cmds_cdio.c \
    $$PWD/DependLibs/libcdio/lib/driver/mmc/mmc_util_cdio.c \
    $$PWD/DependLibs/libcdio/lib/driver/MSWindows/aspi32_cdio.c \
    $$PWD/DependLibs/libcdio/lib/driver/MSWindows/win32_cdio.c \
    $$PWD/DependLibs/libcdio/lib/driver/MSWindows/win32_ioctl_cdio.c \
    $$PWD/DependLibs/libcdio/lib/driver/_cdio_generic_cdio.c \
    $$PWD/DependLibs/libcdio/lib/driver/_cdio_stdio_cdio.c \
    $$PWD/DependLibs/libcdio/lib/driver/_cdio_stream_cdio.c \
    $$PWD/DependLibs/libcdio/lib/driver/abs_path_cdio.c \
    $$PWD/DependLibs/libcdio/lib/driver/aix_cdio.c \
    $$PWD/DependLibs/libcdio/lib/driver/audio_cdio.c \
    $$PWD/DependLibs/libcdio/lib/driver/bsdi_cdio.c \
    $$PWD/DependLibs/libcdio/lib/driver/cd_types_cdio.c \
    $$PWD/DependLibs/libcdio/lib/driver/cdtext_cdio.c \
    $$PWD/DependLibs/libcdio/lib/driver/device_cdio.c \
    $$PWD/DependLibs/libcdio/lib/driver/disc_cdio.c \
    $$PWD/DependLibs/libcdio/lib/driver/ds_cdio.c \
    $$PWD/DependLibs/libcdio/lib/driver/gnu_linux_cdio.c \
    $$PWD/DependLibs/libcdio/lib/driver/image_common_cdio.c \
    $$PWD/DependLibs/libcdio/lib/driver/logging_cdio.c \
    $$PWD/DependLibs/libcdio/lib/driver/memory_cdio.c \
    $$PWD/DependLibs/libcdio/lib/driver/netbsd_cdio.c \
    $$PWD/DependLibs/libcdio/lib/driver/os2_cdio.c \
    $$PWD/DependLibs/libcdio/lib/driver/osx_cdio.c \
    $$PWD/DependLibs/libcdio/lib/driver/read_cdio.c \
    $$PWD/DependLibs/libcdio/lib/driver/realpath_cdio.c \
    $$PWD/DependLibs/libcdio/lib/driver/sector_cdio.c \
    $$PWD/DependLibs/libcdio/lib/driver/solaris_cdio.c \
    $$PWD/DependLibs/libcdio/lib/driver/track_cdio.c \
    $$PWD/DependLibs/libcdio/lib/driver/utf8_cdio.c \
    $$PWD/DependLibs/libcdio/lib/driver/util_cdio.c \
    $$PWD/DependLibs/libcdio/lib/iso9660/iso9660_cdio2.c \
    $$PWD/DependLibs/libcdio/lib/iso9660/iso9660_fs_cdio2.c \
    $$PWD/DependLibs/libcdio/lib/iso9660/rock_cdio.c \
    $$PWD/DependLibs/libcdio/lib/iso9660/xa_cdio.c \
    $$PWD/DependLibs/libcdio/lib/udf/filemode_cdio.c \
    $$PWD/DependLibs/libcdio/lib/udf/udf_cdio.c \
    $$PWD/DependLibs/libcdio/lib/udf/udf_file_cdio.c \
    $$PWD/DependLibs/libcdio/lib/udf/udf_fs_cdio.c \
    $$PWD/DependLibs/libcdio/lib/udf/udf_time_cdio.c

