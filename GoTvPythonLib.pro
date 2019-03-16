

TEMPLATE     = subdirs
CONFIG += no_docs_target

# build the project sequentially as listed in SUBDIRS !
CONFIG += ordered

include(config_os_detect.pri)

#SUBDIRS += $$PWD/python_libeay.pro #static lib build in GoTvDependLibs.pro
#SUBDIRS += $$PWD/python_ssleay.pro #static lib build in GoTvDependLibs.pro

SUBDIRS += $$PWD/libdepends.pro
SUBDIRS += $$PWD/libgnu.pro
#SUBDIRS += $$PWD/libiconv.pro
SUBDIRS += $$PWD/libbz2.pro
SUBDIRS += $$PWD/libcurl.pro
#SUBDIRS += $$PWD/libnetlib.pro
#SUBDIRS += $$PWD/libpktlib.pro
SUBDIRS += $$PWD/libcorelib.pro
SUBDIRS += $$PWD/libcrossguid.pro

SUBDIRS += $$PWD/GoTvOpenSslLib.pro

SUBDIRS += $$PWD/python_pythoncore.pro

SUBDIRS += $$PWD/python_bz2.pro

SUBDIRS += $$PWD/python_ctypes.pro
SUBDIRS += $$PWD/python_ctypes_test.pro
SUBDIRS += $$PWD/python_elementtree.pro
SUBDIRS += $$PWD/python_hashlib.pro
SUBDIRS += $$PWD/python_sqlite3.pro
SUBDIRS += $$PWD/python_socket.pro
SUBDIRS += $$PWD/python_ssl.pro
SUBDIRS += $$PWD/python_testcapi.pro

SUBDIRS += $$PWD/python_pyexpat.pro

SUBDIRS += $$PWD/python_select.pro
SUBDIRS += $$PWD/python_unicodedata.pro

#SUBDIRS += $$PWD/python_bsddb.pro #FIXME does not build

#SUBDIRS += $$PWD/python_tk.pro #FIXME does not build
#SUBDIRS += $$PWD/python_tcl.pro #FIXME does not build
#SUBDIRS += $$PWD/python_tix.pro #FIXME does not build
#SUBDIRS += $$PWD/python_tkinter.pro #FIXME does not build


# sigh.. cannot get qt to exclude these when not builing windows so you will have to uncomment them
#win {
#    SUBDIRS += $$PWD/python_multiprocessing.pro #FIXME does not build
#    SUBDIRS += $$PWD/python_msi.pro
#    SUBDIRS += $$PWD/python_w9xpopen.pro
#    SUBDIRS += $$PWD/python_winsound.pro
#}
