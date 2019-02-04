
INCLUDEPATH += $$PWD/DependLibs
INCLUDEPATH += $$PWD/DependLibs/libpython
INCLUDEPATH += $$PWD/DependLibs/libpython/include

win:{
    INCLUDEPATH += $$PWD/DependLibs/libpython/platform/win
}

unix:!android:{
    INCLUDEPATH += $$PWD/DependLibs/libpython/platform/linux
}

android:{
    INCLUDEPATH += $$PWD/DependLibs/libpython/platform/android
}

HEADERS += 	$$PWD/DependLibs/libpython/Include/Python-ast.h \
    $$PWD/DependLibs/libpython/Include/Python.h \
    $$PWD/DependLibs/libpython/Include/abstract.h \
    $$PWD/DependLibs/libpython/Include/asdl.h \
    $$PWD/DependLibs/libpython/Include/ast.h \
    $$PWD/DependLibs/libpython/Include/bitset.h \
    $$PWD/DependLibs/libpython/Include/boolobject.h \
    $$PWD/DependLibs/libpython/Include/bufferobject.h \
    $$PWD/DependLibs/libpython/Include/bytearrayobject.h \
    $$PWD/DependLibs/libpython/Include/bytes_methods.h \
    $$PWD/DependLibs/libpython/Include/bytesobject.h \
    $$PWD/DependLibs/libpython/Include/cStringIO.h \
    $$PWD/DependLibs/libpython/Include/cellobject.h \
    $$PWD/DependLibs/libpython/Include/ceval.h \
    $$PWD/DependLibs/libpython/Include/classobject.h \
    $$PWD/DependLibs/libpython/Include/cobject.h \
    $$PWD/DependLibs/libpython/Include/code.h \
    $$PWD/DependLibs/libpython/Include/codecs.h \
    $$PWD/DependLibs/libpython/Include/compile.h \
    $$PWD/DependLibs/libpython/Include/complexobject.h \
    $$PWD/DependLibs/libpython/Include/datetime.h \
    $$PWD/DependLibs/libpython/Include/descrobject.h \
    $$PWD/DependLibs/libpython/Include/dictobject.h \
    $$PWD/DependLibs/libpython/Include/dtoa.h \
    $$PWD/DependLibs/libpython/Include/enumobject.h \
    $$PWD/DependLibs/libpython/Include/errcode.h \
    $$PWD/DependLibs/libpython/Include/eval.h \
    $$PWD/DependLibs/libpython/Include/fileobject.h \
    $$PWD/DependLibs/libpython/Include/floatobject.h \
    $$PWD/DependLibs/libpython/Include/frameobject.h \
    $$PWD/DependLibs/libpython/Include/funcobject.h \
    $$PWD/DependLibs/libpython/Include/genobject.h \
    $$PWD/DependLibs/libpython/Include/graminit.h \
    $$PWD/DependLibs/libpython/Include/grammar.h \
    $$PWD/DependLibs/libpython/Include/import.h \
    $$PWD/DependLibs/libpython/Include/intobject.h \
    $$PWD/DependLibs/libpython/Include/intrcheck.h \
    $$PWD/DependLibs/libpython/Include/iterobject.h \
    $$PWD/DependLibs/libpython/Include/listobject.h \
    $$PWD/DependLibs/libpython/Include/longintrepr.h \
    $$PWD/DependLibs/libpython/Include/longobject.h \
    $$PWD/DependLibs/libpython/Include/marshal.h \
    $$PWD/DependLibs/libpython/Include/memoryobject.h \
    $$PWD/DependLibs/libpython/Include/metagrammar.h \
    $$PWD/DependLibs/libpython/Include/methodobject.h \
    $$PWD/DependLibs/libpython/Include/modsupport.h \
    $$PWD/DependLibs/libpython/Include/moduleobject.h \
    $$PWD/DependLibs/libpython/Include/node.h \
    $$PWD/DependLibs/libpython/Include/object.h \
    $$PWD/DependLibs/libpython/Include/objimpl.h \
    $$PWD/DependLibs/libpython/Include/opcode.h \
    $$PWD/DependLibs/libpython/Include/osdefs.h \
    $$PWD/DependLibs/libpython/Include/parsetok.h \
    $$PWD/DependLibs/libpython/Include/patchlevel.h \
    $$PWD/DependLibs/libpython/Include/pgen.h \
    $$PWD/DependLibs/libpython/Include/pgenheaders.h \
    $$PWD/DependLibs/libpython/Include/py_curses.h \
    $$PWD/DependLibs/libpython/Include/pyarena.h \
    $$PWD/DependLibs/libpython/Include/pycapsule.h \
    $$PWD/DependLibs/libpython/Include/pyctype.h \
    $$PWD/DependLibs/libpython/Include/pydebug.h \
    $$PWD/DependLibs/libpython/Include/pyerrors.h \
    $$PWD/DependLibs/libpython/Include/pyexpat.h \
    $$PWD/DependLibs/libpython/Include/pyfpe.h \
    $$PWD/DependLibs/libpython/Include/pygetopt.h \
    $$PWD/DependLibs/libpython/Include/pymactoolbox.h \
    $$PWD/DependLibs/libpython/Include/pymath.h \
    $$PWD/DependLibs/libpython/Include/pymem.h \
    $$PWD/DependLibs/libpython/Include/pyport.h \
    $$PWD/DependLibs/libpython/Include/pystate.h \
    $$PWD/DependLibs/libpython/Include/pystrcmp.h \
    $$PWD/DependLibs/libpython/Include/pystrtod.h \
    $$PWD/DependLibs/libpython/Include/pythonrun.h \
    $$PWD/DependLibs/libpython/Include/pythread.h \
    $$PWD/DependLibs/libpython/Include/rangeobject.h \
    $$PWD/DependLibs/libpython/Include/setobject.h \
    $$PWD/DependLibs/libpython/Include/sliceobject.h \
    $$PWD/DependLibs/libpython/Include/stringobject.h \
    $$PWD/DependLibs/libpython/Include/structmember.h \
    $$PWD/DependLibs/libpython/Include/structseq.h \
    $$PWD/DependLibs/libpython/Include/symtable.h \
    $$PWD/DependLibs/libpython/Include/sysmodule.h \
    $$PWD/DependLibs/libpython/Include/timefuncs.h \
    $$PWD/DependLibs/libpython/Include/token.h \
    $$PWD/DependLibs/libpython/Include/traceback.h \
    $$PWD/DependLibs/libpython/Include/tupleobject.h \
    $$PWD/DependLibs/libpython/Include/ucnhash.h \
    $$PWD/DependLibs/libpython/Include/unicodeobject.h \
    $$PWD/DependLibs/libpython/Include/weakrefobject.h \
    $$PWD/DependLibs/libpython/Modules/_io/_iomodule.h \
    $$PWD/DependLibs/libpython/Modules/_math.h \
    $$PWD/DependLibs/libpython/Modules/cjkcodecs/alg_jisx0201.h \
    $$PWD/DependLibs/libpython/Modules/cjkcodecs/cjkcodecs.h \
    $$PWD/DependLibs/libpython/Modules/cjkcodecs/emu_jisx0213_2000.h \
    $$PWD/DependLibs/libpython/Modules/cjkcodecs/mappings_cn.h \
    $$PWD/DependLibs/libpython/Modules/cjkcodecs/mappings_hk.h \
    $$PWD/DependLibs/libpython/Modules/cjkcodecs/mappings_jisx0213_pair.h \
    $$PWD/DependLibs/libpython/Modules/cjkcodecs/mappings_jp.h \
    $$PWD/DependLibs/libpython/Modules/cjkcodecs/mappings_kr.h \
    $$PWD/DependLibs/libpython/Modules/cjkcodecs/mappings_tw.h \
    $$PWD/DependLibs/libpython/Modules/cjkcodecs/multibytecodec.h \
    $$PWD/DependLibs/libpython/Modules/md5.h \
    $$PWD/DependLibs/libpython/Modules/rotatingtree.h \
    $$PWD/DependLibs/libpython/Modules/zlib/crc32.h \
    $$PWD/DependLibs/libpython/Modules/zlib/deflate.h \
    $$PWD/DependLibs/libpython/Modules/zlib/inffast.h \
    $$PWD/DependLibs/libpython/Modules/zlib/inffixed.h \
    $$PWD/DependLibs/libpython/Modules/zlib/inflate.h \
    $$PWD/DependLibs/libpython/Modules/zlib/inftrees.h \
    $$PWD/DependLibs/libpython/Modules/zlib/trees.h \
    $$PWD/DependLibs/libpython/Modules/zlib/zconf.h \
    $$PWD/DependLibs/libpython/Modules/zlib/zconf.in.h \
    $$PWD/DependLibs/libpython/Modules/zlib/zlib.h \
    $$PWD/DependLibs/libpython/Modules/zlib/zutil.h \
    $$PWD/DependLibs/libpython/Objects/stringlib/count.h \
    $$PWD/DependLibs/libpython/Objects/stringlib/fastsearch.h \
    $$PWD/DependLibs/libpython/Objects/stringlib/find.h \
    $$PWD/DependLibs/libpython/Objects/stringlib/partition.h \
    $$PWD/DependLibs/libpython/Objects/stringlib/split.h \
    $$PWD/DependLibs/libpython/Objects/unicodetype_db.h \
    $$PWD/DependLibs/libpython/Parser/parser.h \
    $$PWD/DependLibs/libpython/Parser/tokenizer.h \
    $$PWD/DependLibs/libpython/Python/importdl.h \
    $$PWD/DependLibs/libpython/Python/thread_nt.h \
    $$PWD/DependLibs/libpython/config_libpython.h

win:{
HEADERS += $$PWD/DependLibs/libpython/platform/win/errmap.h \
    $$PWD/DependLibs/libpython/platform/win/pyconfig.h
}

unix:!android:{
HEADERS += $$PWD/DependLibs/libpython/platform/linux/errmap.h \
    $$PWD/DependLibs/libpython/platform/linux/pyconfig.h
}

android:{
HEADERS += $$PWD/DependLibs/libpython/platform/android/errmap.h \
    $$PWD/DependLibs/libpython/platform/android/pyconfig.h
}

SOURCES += $$PWD/DependLibs/libpython/Modules/_bisectmodule.c \
    $$PWD/DependLibs/libpython/Modules/_codecsmodule.c \
    $$PWD/DependLibs/libpython/Modules/_collectionsmodule.c \
    $$PWD/DependLibs/libpython/Modules/_csv.c \
    $$PWD/DependLibs/libpython/Modules/_functoolsmodule.c \
    $$PWD/DependLibs/libpython/Modules/_heapqmodule.c \
    $$PWD/DependLibs/libpython/Modules/_hotshot.c \
    $$PWD/DependLibs/libpython/Modules/_io/_iomodule.c \
    $$PWD/DependLibs/libpython/Modules/_io/bufferedio.c \
    $$PWD/DependLibs/libpython/Modules/_io/bytesio.c \
    $$PWD/DependLibs/libpython/Modules/_io/fileio.c \
    $$PWD/DependLibs/libpython/Modules/_io/iobase.c \
    $$PWD/DependLibs/libpython/Modules/_io/stringio.c \
    $$PWD/DependLibs/libpython/Modules/_io/textio.c \
    $$PWD/DependLibs/libpython/Modules/_json.c \
    $$PWD/DependLibs/libpython/Modules/_localemodule.c \
    $$PWD/DependLibs/libpython/Modules/_lsprof.c \
    $$PWD/DependLibs/libpython/Modules/_math.c \
    $$PWD/DependLibs/libpython/Modules/_randommodule.c \
    $$PWD/DependLibs/libpython/Modules/_sre.c \
    $$PWD/DependLibs/libpython/Modules/_struct.c \
    $$PWD/DependLibs/libpython/Modules/_weakref.c \
    $$PWD/DependLibs/libpython/Modules/arraymodule.c \
    $$PWD/DependLibs/libpython/Modules/audioop.c \
    $$PWD/DependLibs/libpython/Modules/binascii.c \
    $$PWD/DependLibs/libpython/Modules/cPickle.c \
    $$PWD/DependLibs/libpython/Modules/cStringIO.c \
    $$PWD/DependLibs/libpython/Modules/cjkcodecs/_codecs_cn.c \
    $$PWD/DependLibs/libpython/Modules/cjkcodecs/_codecs_hk.c \
    $$PWD/DependLibs/libpython/Modules/cjkcodecs/_codecs_iso2022.c \
    $$PWD/DependLibs/libpython/Modules/cjkcodecs/_codecs_jp.c \
    $$PWD/DependLibs/libpython/Modules/cjkcodecs/_codecs_kr.c \
    $$PWD/DependLibs/libpython/Modules/cjkcodecs/_codecs_tw.c \
    $$PWD/DependLibs/libpython/Modules/cjkcodecs/multibytecodec.c \
    $$PWD/DependLibs/libpython/Modules/cmathmodule.c \
    $$PWD/DependLibs/libpython/Modules/datetimemodule.c \
    $$PWD/DependLibs/libpython/Modules/errnomodule.c \
    $$PWD/DependLibs/libpython/Modules/future_builtins.c \
    $$PWD/DependLibs/libpython/Modules/gcmodule.c \
    $$PWD/DependLibs/libpython/Modules/getbuildinfo.c \
    $$PWD/DependLibs/libpython/Modules/imageop.c \
    $$PWD/DependLibs/libpython/Modules/itertoolsmodule.c \
    $$PWD/DependLibs/libpython/Modules/main.c \
    $$PWD/DependLibs/libpython/Modules/mathmodule.c \
    $$PWD/DependLibs/libpython/Modules/md5.c \
    $$PWD/DependLibs/libpython/Modules/md5module.c \
    $$PWD/DependLibs/libpython/Modules/mmapmodule.c \
    $$PWD/DependLibs/libpython/Modules/operator.c \
    $$PWD/DependLibs/libpython/Modules/parsermodule.c \
    $$PWD/DependLibs/libpython/Modules/posixmodule.c \
    $$PWD/DependLibs/libpython/Modules/rotatingtree.c \
    $$PWD/DependLibs/libpython/Modules/sha256module.c \
    $$PWD/DependLibs/libpython/Modules/sha512module.c \
    $$PWD/DependLibs/libpython/Modules/shamodule.c \
    $$PWD/DependLibs/libpython/Modules/signalmodule.c \
    $$PWD/DependLibs/libpython/Modules/stropmodule.c \
    $$PWD/DependLibs/libpython/Modules/symtablemodule.c \
    $$PWD/DependLibs/libpython/Modules/threadmodule.c \
    $$PWD/DependLibs/libpython/Modules/timemodule.c \
    $$PWD/DependLibs/libpython/Modules/xxsubtype.c \
    $$PWD/DependLibs/libpython/Modules/zipimport.c \
    $$PWD/DependLibs/libpython/Modules/zlib/adler32.c \
    $$PWD/DependLibs/libpython/Modules/zlib/compress.c \
    $$PWD/DependLibs/libpython/Modules/zlib/crc32.c \
    $$PWD/DependLibs/libpython/Modules/zlib/deflate.c \
    $$PWD/DependLibs/libpython/Modules/zlib/gzclose.c \
    $$PWD/DependLibs/libpython/Modules/zlib/gzlib.c \
    $$PWD/DependLibs/libpython/Modules/zlib/gzread.c \
    $$PWD/DependLibs/libpython/Modules/zlib/gzwrite.c \
    $$PWD/DependLibs/libpython/Modules/zlib/infback.c \
    $$PWD/DependLibs/libpython/Modules/zlib/inffast.c \
    $$PWD/DependLibs/libpython/Modules/zlib/inflate.c \
    $$PWD/DependLibs/libpython/Modules/zlib/inftrees.c \
    $$PWD/DependLibs/libpython/Modules/zlib/trees.c \
    $$PWD/DependLibs/libpython/Modules/zlib/uncompr.c \
    $$PWD/DependLibs/libpython/Modules/zlib/zutil.c \
    $$PWD/DependLibs/libpython/Modules/zlibmodule.c \
    $$PWD/DependLibs/libpython/Objects/abstract.c \
    $$PWD/DependLibs/libpython/Objects/boolobject.c \
    $$PWD/DependLibs/libpython/Objects/bufferobject.c \
    $$PWD/DependLibs/libpython/Objects/bytearrayobject.c \
    $$PWD/DependLibs/libpython/Objects/bytes_methods.c \
    $$PWD/DependLibs/libpython/Objects/capsule.c \
    $$PWD/DependLibs/libpython/Objects/cellobject.c \
    $$PWD/DependLibs/libpython/Objects/classobject.c \
    $$PWD/DependLibs/libpython/Objects/cobject.c \
    $$PWD/DependLibs/libpython/Objects/codeobject.c \
    $$PWD/DependLibs/libpython/Objects/complexobject.c \
    $$PWD/DependLibs/libpython/Objects/descrobject.c \
    $$PWD/DependLibs/libpython/Objects/dictobject.c \
    $$PWD/DependLibs/libpython/Objects/enumobject.c \
    $$PWD/DependLibs/libpython/Objects/exceptions.c \
    $$PWD/DependLibs/libpython/Objects/fileobject.c \
    $$PWD/DependLibs/libpython/Objects/floatobject.c \
    $$PWD/DependLibs/libpython/Objects/frameobject.c \
    $$PWD/DependLibs/libpython/Objects/funcobject.c \
    $$PWD/DependLibs/libpython/Objects/genobject.c \
    $$PWD/DependLibs/libpython/Objects/intobject.c \
    $$PWD/DependLibs/libpython/Objects/iterobject.c \
    $$PWD/DependLibs/libpython/Objects/listobject.c \
    $$PWD/DependLibs/libpython/Objects/longobject.c \
    $$PWD/DependLibs/libpython/Objects/memoryobject.c \
    $$PWD/DependLibs/libpython/Objects/methodobject.c \
    $$PWD/DependLibs/libpython/Objects/moduleobject.c \
    $$PWD/DependLibs/libpython/Objects/object.c \
    $$PWD/DependLibs/libpython/Objects/obmalloc.c \
    $$PWD/DependLibs/libpython/Objects/rangeobject.c \
    $$PWD/DependLibs/libpython/Objects/setobject.c \
    $$PWD/DependLibs/libpython/Objects/sliceobject.c \
    $$PWD/DependLibs/libpython/Objects/stringobject.c \
    $$PWD/DependLibs/libpython/Objects/structseq.c \
    $$PWD/DependLibs/libpython/Objects/tupleobject.c \
    $$PWD/DependLibs/libpython/Objects/typeobject.c \
    $$PWD/DependLibs/libpython/Objects/unicodectype.c \
    $$PWD/DependLibs/libpython/Objects/unicodeobject.c \
    $$PWD/DependLibs/libpython/Objects/weakrefobject.c \
    $$PWD/DependLibs/libpython/Parser/acceler.c \
    $$PWD/DependLibs/libpython/Parser/bitset.c \
    $$PWD/DependLibs/libpython/Parser/firstsets.c \
    $$PWD/DependLibs/libpython/Parser/grammar.c \
    $$PWD/DependLibs/libpython/Parser/grammar1.c \
    $$PWD/DependLibs/libpython/Parser/listnode.c \
    $$PWD/DependLibs/libpython/Parser/metagrammar.c \
    $$PWD/DependLibs/libpython/Parser/myreadline.c \
    $$PWD/DependLibs/libpython/Parser/node.c \
    $$PWD/DependLibs/libpython/Parser/parser.c \
    $$PWD/DependLibs/libpython/Parser/parsetok.c \
    $$PWD/DependLibs/libpython/Parser/tokenizer.c \
    $$PWD/DependLibs/libpython/Python/Python-ast.c \
    $$PWD/DependLibs/libpython/Python/_warnings.c \
    $$PWD/DependLibs/libpython/Python/asdl.c \
    $$PWD/DependLibs/libpython/Python/ast.c \
    $$PWD/DependLibs/libpython/Python/bltinmodule.c \
    $$PWD/DependLibs/libpython/Python/ceval.c \
    $$PWD/DependLibs/libpython/Python/codecs.c \
    $$PWD/DependLibs/libpython/Python/compile.c \
    $$PWD/DependLibs/libpython/Python/dtoa.c \
    $$PWD/DependLibs/libpython/Python/dynload_win.c \
    $$PWD/DependLibs/libpython/Python/errors.c \
    $$PWD/DependLibs/libpython/Python/formatter_string.c \
    $$PWD/DependLibs/libpython/Python/formatter_unicode.c \
    $$PWD/DependLibs/libpython/Python/frozen.c \
    $$PWD/DependLibs/libpython/Python/future.c \
    $$PWD/DependLibs/libpython/Python/getargs.c \
    $$PWD/DependLibs/libpython/Python/getcompiler.c \
    $$PWD/DependLibs/libpython/Python/getcopyright.c \
    $$PWD/DependLibs/libpython/Python/getopt.c \
    $$PWD/DependLibs/libpython/Python/getplatform.c \
    $$PWD/DependLibs/libpython/Python/getversion.c \
    $$PWD/DependLibs/libpython/Python/graminit.c \
    $$PWD/DependLibs/libpython/Python/import.c \
    $$PWD/DependLibs/libpython/Python/importdl.c \
    $$PWD/DependLibs/libpython/Python/marshal.c \
    $$PWD/DependLibs/libpython/Python/modsupport.c \
    $$PWD/DependLibs/libpython/Python/mysnprintf.c \
    $$PWD/DependLibs/libpython/Python/mystrtoul.c \
    $$PWD/DependLibs/libpython/Python/peephole.c \
    $$PWD/DependLibs/libpython/Python/pyarena.c \
    $$PWD/DependLibs/libpython/Python/pyctype.c \
    $$PWD/DependLibs/libpython/Python/pyfpe.c \
    $$PWD/DependLibs/libpython/Python/pymath.c \
    $$PWD/DependLibs/libpython/Python/pystate.c \
    $$PWD/DependLibs/libpython/Python/pystrcmp.c \
    $$PWD/DependLibs/libpython/Python/pystrtod.c \
    $$PWD/DependLibs/libpython/Python/pythonrun.c \
    $$PWD/DependLibs/libpython/Python/random.c \
    $$PWD/DependLibs/libpython/Python/structmember.c \
    $$PWD/DependLibs/libpython/Python/symtable.c \
    $$PWD/DependLibs/libpython/Python/sysmodule.c \
    $$PWD/DependLibs/libpython/Python/thread.c \
    $$PWD/DependLibs/libpython/Python/traceback.c


win:{
SOURCES += $$PWD/DependLibs/libpython/platform/win/_subprocess.c \
    $$PWD/DependLibs/libpython/platform/win/_winreg.c \
    $$PWD/DependLibs/libpython/platform/win/config.c \
    $$PWD/DependLibs/libpython/platform/win/dl_nt.c \
    $$PWD/DependLibs/libpython/platform/win/getpathp.c \
    $$PWD/DependLibs/libpython/platform/win/import_nt.c \
    $$PWD/DependLibs/libpython/platform/win/msvcrtmodule.c
}

unix:!android:{
#    $$PWD/DependLibs/libpython/platform/linux/pyconfig.h
}

android:{
#    $$PWD/DependLibs/libpython/platform/android/pyconfig.h
}



