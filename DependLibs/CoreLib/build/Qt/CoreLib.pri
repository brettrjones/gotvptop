
DEFINES += "STATICLIB"
DEFINES += "SQLITE_OMIT_LOAD_EXTENSION"

HEADERS += 	$$PWD/../../../../GoTvCompilerConfig.h \
    $$PWD/../../../../GoTvAppConfig.h \
	$$PWD/../../../../GoTvCpuArchDefines.h \
	$$PWD/../../../../GoTvDependLibrariesConfig.h \
	$$PWD/../../../../GoTvTargetOsConfig.h \
	$$PWD/../../../../arpa/inet.h \
	$$PWD/../../../../asm/types.h \
	$$PWD/../../../../byteswap.h \
	$$PWD/../../../../dirent.h \
	$$PWD/../../../../dlfcn.h \
	$$PWD/../../../../langinfo.h \
	$$PWD/../../../../linux/ioctl.h \
	$$PWD/../../../../linux/param.h \
	$$PWD/../../../../netdb.h \
	$$PWD/../../../../netinet/in.h \
	$$PWD/../../../../netinet/tcp.h \
	$$PWD/../../../../strings.h \
	$$PWD/../../../../sys/ioctl.h \
	$$PWD/../../../../sys/mman.h \
	$$PWD/../../../../sys/param.h \
	$$PWD/../../../../sys/select.h \
	$$PWD/../../../../sys/signal.h \
	$$PWD/../../../../sys/socket.h \
	$$PWD/../../../../sys/syslog.h \
	$$PWD/../../../../sys/time.h \
	$$PWD/../../../../sys/times.h \
	$$PWD/../../../../sys/un.h \
	$$PWD/../../../../sys/utsname.h \
	$$PWD/../../../../syslog.h \
	$$PWD/../../../../unistd.h \
	$$PWD/../../AppErr.h \
	$$PWD/../../AssetDefs.h \
	$$PWD/../../Blowfish.h \
	$$PWD/../../DbBase.h \
	$$PWD/../../DbDataset.h \
	$$PWD/../../DbQueryData.h \
	$$PWD/../../IsBigEndianCpu.h \
	$$PWD/../../MediaCallbackInterface.h \
	$$PWD/../../OsDetect.h \
	$$PWD/../../SHA1.h \
	$$PWD/../../StdOutRedirect.h \
	$$PWD/../../VarToString.h \
	$$PWD/../../VxAppInfo.h \
	$$PWD/../../VxBuffer.h \
	$$PWD/../../VxChop.h \
	$$PWD/../../VxChopMap.h \
	$$PWD/../../VxColorUtil.h \
	$$PWD/../../VxCrypto.h \
	$$PWD/../../VxDebug.h \
	$$PWD/../../VxDefs.h \
	$$PWD/../../VxFileCrc32.h \
	$$PWD/../../VxFileInfo.h \
	$$PWD/../../VxFileIsTypeFunctions.h \
	$$PWD/../../VxFileLists.h \
	$$PWD/../../VxFileShredder.h \
	$$PWD/../../VxFileShredderDb.h \
	$$PWD/../../VxFileTypeMasks.h \
	$$PWD/../../VxFileUtil.h \
	$$PWD/../../VxGUID.h \
	$$PWD/../../VxGUIDList.h \
	$$PWD/../../VxGlobals.h \
	$$PWD/../../VxKeyDefs.h \
	$$PWD/../../VxLinuxOnly.h \
	$$PWD/../../VxMacros.h \
	$$PWD/../../VxMathDef.h \
	$$PWD/../../VxMathVec2f.h \
	$$PWD/../../VxMathVec3f.h \
	$$PWD/../../VxMathVec4f.h \
	$$PWD/../../VxMutex.h \
	$$PWD/../../VxParse.h \
	$$PWD/../../VxProfile.h \
	$$PWD/../../VxRefCount.h \
	$$PWD/../../VxSemaphore.h \
	$$PWD/../../VxSettings.h \
	$$PWD/../../VxSha1Hash.h \
	$$PWD/../../VxShortcut.h \
	$$PWD/../../VxSingleton.h \
	$$PWD/../../VxSupportedFiles.h \
	$$PWD/../../VxTextStreamReader.h \
	$$PWD/../../VxThread.h \
	$$PWD/../../VxTimeDefs.h \
	$$PWD/../../VxTimeUtil.h \
	$$PWD/../../VxTimer.h \
	$$PWD/../../VxValuePair.h \
	$$PWD/../../VxXml.h \
	$$PWD/../../dirent_sim.h \
	$$PWD/../../md5.h \
	$$PWD/../../rsa.h \
#	$$PWD/../../sqlite3.h \
#	$$PWD/../../sqlite3ext.h \
#	$$PWD/../../sqlitedataset.h

SOURCES += 	$$PWD/../../AppErr.cpp \
	$$PWD/../../Blowfish.cpp \
	$$PWD/../../DbBase.cpp \
	$$PWD/../../DbDataset.cpp \
	$$PWD/../../DbQueryData.cpp \
	$$PWD/../../OsDetect.cpp \
	$$PWD/../../SHA1.cpp \
	$$PWD/../../StdOutRedirect.cpp \
	$$PWD/../../VxAppInfo.cpp \
	$$PWD/../../VxBuffer.cpp \
	$$PWD/../../VxChop.cpp \
	$$PWD/../../VxChopMap.cpp \
	$$PWD/../../VxColorUtil.cpp \
	$$PWD/../../VxCrypto.cpp \
	$$PWD/../../VxDebug.cpp \
	$$PWD/../../VxDefs.cpp \
	$$PWD/../../VxFileCrc32.cpp \
	$$PWD/../../VxFileInfo.cpp \
	$$PWD/../../VxFileIsTypeFunctions.cpp \
	$$PWD/../../VxFileLists.cpp \
	$$PWD/../../VxFileShredder.cpp \
	$$PWD/../../VxFileShredderDb.cpp \
	$$PWD/../../VxFileUtil.cpp \
    $$PWD/../../VxFunctionsMissingInPosix.cpp \
    $$PWD/../../VxFunctionsMissingInWindows.cpp \
	$$PWD/../../VxGUID.cpp \
	$$PWD/../../VxGUIDList.cpp \
	$$PWD/../../VxGlobals.cpp \
	$$PWD/../../VxLinuxOnly.cpp \
	$$PWD/../../VxMathDef.cpp \
	$$PWD/../../VxMathVec3f.cpp \
	$$PWD/../../VxMutex.cpp \
	$$PWD/../../VxParse.cpp \
	$$PWD/../../VxProfile.cpp \
	$$PWD/../../VxRefCount.cpp \
	$$PWD/../../VxSemaphore.cpp \
	$$PWD/../../VxSettings.cpp \
	$$PWD/../../VxSha1Hash.cpp \
	$$PWD/../../VxShortcut.cpp \
	$$PWD/../../VxTextStreamReader.cpp \
	$$PWD/../../VxThread.cpp \
	$$PWD/../../VxTimeUtil.cpp \
	$$PWD/../../VxTimer.cpp \
	$$PWD/../../VxValuePair.cpp \
	$$PWD/../../VxXml.cpp \
	$$PWD/../../md5.c \
	$$PWD/../../rsa_eay.c \
	$$PWD/../../rsa_gen.c \
    $$PWD/../../sqlite3.c \
    $$PWD/../../sqlitedataset.cpp

