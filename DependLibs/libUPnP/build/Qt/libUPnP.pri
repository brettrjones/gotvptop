
INCLUDEPATH += $$PWD/../../
INCLUDEPATH += $$PWD/../../Platinum/Source/Platinum
INCLUDEPATH += $$PWD/../../Platinum/Source/Core
INCLUDEPATH += $$PWD/../../Platinum/Source/Extras
INCLUDEPATH += $$PWD/../../Platinum/Source/Devices/MediaServer
INCLUDEPATH += $$PWD/../../Platinum/Source/Devices/MediaRenderer
INCLUDEPATH += $$PWD/../../Platinum/Source/Devices/MediaConnect
INCLUDEPATH += $$PWD/../../Neptune/Source/Core
win32{
INCLUDEPATH += $$PWD/../../Neptune/Source/System/Win32
}

HEADERS += 	$$PWD/../../../../GoTvCompilerConfig.h \
	$$PWD/../../../../GoTvCpuArchDefines.h \
	$$PWD/../../../../GoTvDependLibrariesConfig.h \
	$$PWD/../../../../GoTvTargetOsConfig.h \
	$$PWD/../../../../base64.h \
	$$PWD/../../../../byteswap.h \
	$$PWD/../../../../dirent.h \
	$$PWD/../../../../dlfcn.h \
	$$PWD/../../../../langinfo.h \
	$$PWD/../../../../netdb.h \
	$$PWD/../../../../pwd.h \
	$$PWD/../../../../strings.h \
	$$PWD/../../../../syslog.h \
	$$PWD/../../../../unistd.h \
	$$PWD/../../../../utime.h \
	$$PWD/../../Platinum/Source/Core/PltAction.h \
	$$PWD/../../Platinum/Source/Core/PltArgument.h \
	$$PWD/../../Platinum/Source/Core/PltConstants.h \
	$$PWD/../../Platinum/Source/Core/PltCtrlPoint.h \
	$$PWD/../../Platinum/Source/Core/PltCtrlPointTask.h \
	$$PWD/../../Platinum/Source/Core/PltDatagramStream.h \
	$$PWD/../../Platinum/Source/Core/PltDeviceData.h \
	$$PWD/../../Platinum/Source/Core/PltDeviceHost.h \
	$$PWD/../../Platinum/Source/Core/PltEvent.h \
	$$PWD/../../Platinum/Source/Core/PltHttp.h \
	$$PWD/../../Platinum/Source/Core/PltHttpClientTask.h \
	$$PWD/../../Platinum/Source/Core/PltHttpServer.h \
	$$PWD/../../Platinum/Source/Core/PltHttpServerListener.h \
	$$PWD/../../Platinum/Source/Core/PltHttpServerTask.h \
	$$PWD/../../Platinum/Source/Core/PltMimeType.h \
	$$PWD/../../Platinum/Source/Core/PltProtocolInfo.h \
	$$PWD/../../Platinum/Source/Core/PltService.h \
	$$PWD/../../Platinum/Source/Core/PltSsdp.h \
	$$PWD/../../Platinum/Source/Core/PltSsdpListener.h \
	$$PWD/../../Platinum/Source/Core/PltStateVariable.h \
	$$PWD/../../Platinum/Source/Core/PltTaskManager.h \
	$$PWD/../../Platinum/Source/Core/PltThreadTask.h \
	$$PWD/../../Platinum/Source/Core/PltUPnP.h \
	$$PWD/../../Platinum/Source/Core/PltUPnPHelper.h \
	$$PWD/../../Platinum/Source/Core/PltXmlHelper.h \
	$$PWD/../../Platinum/Source/Devices/MediaConnect/PltMediaConnect.h \
	$$PWD/../../Platinum/Source/Devices/MediaConnect/PltXbox360.h \
	$$PWD/../../Platinum/Source/Devices/MediaRenderer/PltMediaController.h \
	$$PWD/../../Platinum/Source/Devices/MediaRenderer/PltMediaControllerListener.h \
	$$PWD/../../Platinum/Source/Devices/MediaRenderer/PltMediaRenderer.h \
	$$PWD/../../Platinum/Source/Devices/MediaServer/PltDidl.h \
	$$PWD/../../Platinum/Source/Devices/MediaServer/PltFileMediaServer.h \
	$$PWD/../../Platinum/Source/Devices/MediaServer/PltMediaBrowser.h \
	$$PWD/../../Platinum/Source/Devices/MediaServer/PltMediaBrowserListener.h \
	$$PWD/../../Platinum/Source/Devices/MediaServer/PltMediaCache.h \
	$$PWD/../../Platinum/Source/Devices/MediaServer/PltMediaItem.h \
	$$PWD/../../Platinum/Source/Devices/MediaServer/PltMediaServer.h \
	$$PWD/../../Platinum/Source/Devices/MediaServer/PltSyncMediaBrowser.h \
	$$PWD/../../Platinum/Source/Extras/PltDownloader.h \
	$$PWD/../../Platinum/Source/Extras/PltFrameBuffer.h \
	$$PWD/../../Platinum/Source/Extras/PltFrameServer.h \
	$$PWD/../../Platinum/Source/Extras/PltFrameStream.h \
	$$PWD/../../Platinum/Source/Extras/PltLeaks.h \
	$$PWD/../../Platinum/Source/Extras/PltMetadataHandler.h \
	$$PWD/../../Platinum/Source/Extras/PltRingBufferStream.h \
	$$PWD/../../Platinum/Source/Extras/PltStreamPump.h \
	$$PWD/../../Platinum/Source/Platinum/Platinum.h \
	$$PWD/../../Platinum/Source/Platinum/PltSvnVersion.h \
	$$PWD/../../Platinum/Source/Platinum/PltVersion.h \
	$$PWD/../../config_libupnp.h

SOURCES += 	$$PWD/../../Platinum/Source/Core/PltAction.cpp \
	$$PWD/../../Platinum/Source/Core/PltArgument.cpp \
	$$PWD/../../Platinum/Source/Core/PltConstants.cpp \
	$$PWD/../../Platinum/Source/Core/PltCtrlPoint.cpp \
	$$PWD/../../Platinum/Source/Core/PltCtrlPointTask.cpp \
	$$PWD/../../Platinum/Source/Core/PltDatagramStream.cpp \
	$$PWD/../../Platinum/Source/Core/PltDeviceData.cpp \
	$$PWD/../../Platinum/Source/Core/PltDeviceHost.cpp \
	$$PWD/../../Platinum/Source/Core/PltEvent.cpp \
	$$PWD/../../Platinum/Source/Core/PltHttp.cpp \
	$$PWD/../../Platinum/Source/Core/PltHttpClientTask.cpp \
	$$PWD/../../Platinum/Source/Core/PltHttpServer.cpp \
	$$PWD/../../Platinum/Source/Core/PltHttpServerTask.cpp \
	$$PWD/../../Platinum/Source/Core/PltIconsData.cpp \
	$$PWD/../../Platinum/Source/Core/PltMimeType.cpp \
	$$PWD/../../Platinum/Source/Core/PltProtocolInfo.cpp \
	$$PWD/../../Platinum/Source/Core/PltService.cpp \
	$$PWD/../../Platinum/Source/Core/PltSsdp.cpp \
	$$PWD/../../Platinum/Source/Core/PltStateVariable.cpp \
	$$PWD/../../Platinum/Source/Core/PltTaskManager.cpp \
	$$PWD/../../Platinum/Source/Core/PltThreadTask.cpp \
	$$PWD/../../Platinum/Source/Core/PltUPnP.cpp \
	$$PWD/../../Platinum/Source/Devices/MediaConnect/PltMediaConnect.cpp \
	$$PWD/../../Platinum/Source/Devices/MediaConnect/PltXbox360.cpp \
	$$PWD/../../Platinum/Source/Devices/MediaConnect/X_MS_MediaReceiverRegistrarSCPD.cpp \
	$$PWD/../../Platinum/Source/Devices/MediaRenderer/AVTransportSCPD.cpp \
	$$PWD/../../Platinum/Source/Devices/MediaRenderer/PltMediaController.cpp \
	$$PWD/../../Platinum/Source/Devices/MediaRenderer/PltMediaRenderer.cpp \
	$$PWD/../../Platinum/Source/Devices/MediaRenderer/RdrConnectionManagerSCPD.cpp \
	$$PWD/../../Platinum/Source/Devices/MediaRenderer/RenderingControlSCPD.cpp \
	$$PWD/../../Platinum/Source/Devices/MediaServer/ConnectionManagerSCPD.cpp \
	$$PWD/../../Platinum/Source/Devices/MediaServer/ContentDirectorySCPD.cpp \
	$$PWD/../../Platinum/Source/Devices/MediaServer/ContentDirectorywSearchSCPD.cpp \
	$$PWD/../../Platinum/Source/Devices/MediaServer/PltDidl.cpp \
	$$PWD/../../Platinum/Source/Devices/MediaServer/PltFileMediaServer.cpp \
	$$PWD/../../Platinum/Source/Devices/MediaServer/PltMediaBrowser.cpp \
	$$PWD/../../Platinum/Source/Devices/MediaServer/PltMediaCache.cpp \
	$$PWD/../../Platinum/Source/Devices/MediaServer/PltMediaItem.cpp \
	$$PWD/../../Platinum/Source/Devices/MediaServer/PltMediaServer.cpp \
	$$PWD/../../Platinum/Source/Devices/MediaServer/PltSyncMediaBrowser.cpp \
	$$PWD/../../Platinum/Source/Extras/PltDownloader.cpp \
	$$PWD/../../Platinum/Source/Extras/PltFrameBuffer.cpp \
	$$PWD/../../Platinum/Source/Extras/PltFrameServer.cpp \
	$$PWD/../../Platinum/Source/Extras/PltFrameStream.cpp \
	$$PWD/../../Platinum/Source/Extras/PltLeaks.cpp \
	$$PWD/../../Platinum/Source/Extras/PltMetadataHandler.cpp \
	$$PWD/../../Platinum/Source/Extras/PltRingBufferStream.cpp \
	$$PWD/../../Platinum/Source/Extras/PltStreamPump.cpp

