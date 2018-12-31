message("Building GoTvPtoP")

INCLUDEPATH += $$PWD/../../../
INCLUDEPATH += $$PWD/../../../../GoTvCore

HEADERS += $$PWD/../../../GoTvCommon/QtSource/MyIconsDefs.h \
    $$PWD/../../../GoTvCommon/QtSource/VxDataHelper.h \
    $$PWD/../../../GoTvCommon/QtSource/FileItemInfo.h \
    $$PWD/../../../GoTvCommon/QtSource/Friend.h \
    $$PWD/../../../GoTvCommon/QtSource/FriendList.h \
    $$PWD/../../../GoTvCommon/QtSource/FriendListDelegate.h \
    $$PWD/../../../GoTvCommon/QtSource/GuiFileXferSession.h \
    $$PWD/../../../GoTvCommon/QtSource/GuiHelpers.h \
    $$PWD/../../../GoTvCommon/QtSource/MyIcons.h \
    $$PWD/../../../GoTvCommon/QtSource/OfferSessionCallbackInterface.h \
    $$PWD/../../../GoTvCommon/QtSource/OfferSessionLogic.h \
    $$PWD/../../../GoTvCommon/QtSource/OfferSessionState.h \
    $$PWD/../../../GoTvCommon/QtSource/PopupMenuDelegate.h \
    $$PWD/../../../GoTvCommon/QtSource/SoundDefs.h \
    $$PWD/../../../GoTvCommon/QtSource/ToGuiActivityClient.h \
    $$PWD/../../../GoTvCommon/QtSource/ToGuiActivityInterface.h \
    $$PWD/../../../GoTvCommon/QtSource/ToGuiFileXferClient.h \
    $$PWD/../../../GoTvCommon/QtSource/ToGuiFileXferInterface.h \
    $$PWD/../../../GoTvCommon/QtSource/ToGuiHardwareControlInterface.h \
    $$PWD/../../../GoTvCommon/QtSource/ToGuiHardwareCtrlClient.h \
    $$PWD/../../../GoTvCommon/QtSource/ToGuiOfferInterface.h \
    $$PWD/../../../GoTvCommon/QtSource/UserProfile.h \
    $$PWD/../../../GoTvCommon/QtSource/AnalogClock.h \
    $$PWD/../../../GoTvCommon/QtSource/MessengerPage.h \
    $$PWD/../../../GoTvCommon/QtSource/DialogConfirmRemoveMessage.h \
    $$PWD/../../../GoTvCommon/QtSource/FileActionBarWidget.h \
    $$PWD/../../../GoTvCommon/QtSource/FileActionMenu.h \
    $$PWD/../../../GoTvCommon/QtSource/FileItemWidget.h \
    $$PWD/../../../GoTvCommon/QtSource/FileListReplySession.h \
    $$PWD/../../../GoTvCommon/QtSource/FileShareItemWidget.h \
    $$PWD/../../../GoTvCommon/QtSource/FileXferWidget.h \
    $$PWD/../../../GoTvCommon/QtSource/FriendListWidget.h \
    $$PWD/../../../GoTvCommon/QtSource/GuiFileActionSession.h \
    $$PWD/../../../GoTvCommon/QtSource/GuiOfferSession.h \
    $$PWD/../../../GoTvCommon/QtSource/HistoryEntryWidget.h \
    $$PWD/../../../GoTvCommon/QtSource/HistoryListWidget.h \
    $$PWD/../../../GoTvCommon/QtSource/IdentWidget.h \
    $$PWD/../../../GoTvCommon/QtSource/InstMsgWidget.h \
    $$PWD/../../../GoTvCommon/QtSource/MultiSessionState.h \
    $$PWD/../../../GoTvCommon/QtSource/TitleBarWidget.h \
    $$PWD/../../../GoTvCommon/QtSource/OfferBarWidget.h \
    $$PWD/../../../GoTvCommon/QtSource/OffersMgr.h \
    $$PWD/../../../GoTvCommon/QtSource/OfferWidget.h \
    $$PWD/../../../GoTvCommon/QtSource/PopupMenu.h \
    $$PWD/../../../GoTvCommon/QtSource/VxMenu.h \
    $$PWD/../../../GoTvCommon/QtSource/SessionWidget.h \
    $$PWD/../../../GoTvCommon/QtSource/SoundCtrlWidget.h \
    $$PWD/../../../GoTvCommon/QtSource/StoryWidget.h \
    $$PWD/../../../GoTvCommon/QtSource/TextChatLogic.h \
    $$PWD/../../../GoTvCommon/QtSource/RasterWindow.h \
    $$PWD/../../../GoTvCommon/QtSource/ChatEntryWidget.h \
    $$PWD/../../../GoTvCommon/QtSource/InputAllWidget.h \
    $$PWD/../../../GoTvCommon/QtSource/InputBaseWidget.h \
    $$PWD/../../../GoTvCommon/QtSource/InputFaceWidget.h \
    $$PWD/../../../GoTvCommon/QtSource/InputPhotoWidget.h \
    $$PWD/../../../GoTvCommon/QtSource/InputTextWidget.h \
    $$PWD/../../../GoTvCommon/QtSource/InputVideoWidget.h \
    $$PWD/../../../GoTvCommon/QtSource/InputVoiceWidget.h \
    $$PWD/../../../GoTvCommon/QtSource/ActivityAbout.h \
    $$PWD/../../../GoTvCommon/QtSource/ActivityAddRemoveLibraryFiles.h \
    $$PWD/../../../GoTvCommon/QtSource/ActivityAnchorSettings.h \
    $$PWD/../../../GoTvCommon/QtSource/ActivityBrowseFiles.h \
    $$PWD/../../../GoTvCommon/QtSource/ActivityChooseIpPort.h \
    $$PWD/../../../GoTvCommon/QtSource/ActivityChooseTestWebsiteUrl.h \
    $$PWD/../../../GoTvCommon/QtSource/ActivityCreateProfile.h \
    $$PWD/../../../GoTvCommon/QtSource/ActivityDebugSettings.h \
    $$PWD/../../../GoTvCommon/QtSource/ActivityDownloadItemMenu.h \
    $$PWD/../../../GoTvCommon/QtSource/ActivityDownloads.h \
    $$PWD/../../../GoTvCommon/QtSource/ActivityEditAccount.h \
    $$PWD/../../../GoTvCommon/QtSource/ActivityEditProfile.h \
    $$PWD/../../../GoTvCommon/QtSource/ActivityFileSearch.h \
    $$PWD/../../../GoTvCommon/QtSource/ActivityIsPortOpenTest.h \
    $$PWD/../../../GoTvCommon/QtSource/ActivityManageAnchorSettings.h \
    $$PWD/../../../GoTvCommon/QtSource/ActivityMessageBox.h \
    $$PWD/../../../GoTvCommon/QtSource/ActivityNetServiceTest.h \
    $$PWD/../../../GoTvCommon/QtSource/ActivityNetworkSettings.h \
    $$PWD/../../../GoTvCommon/QtSource/ActivityNetworkState.h \
    $$PWD/../../../GoTvCommon/QtSource/ActivityPermissions.h \
    $$PWD/../../../GoTvCommon/QtSource/ActivityPermissionsRelay.h \
    $$PWD/../../../GoTvCommon/QtSource/ActivityPersonalRecorder.h \
    $$PWD/../../../GoTvCommon/QtSource/ActivityPhoneShake.h \
    $$PWD/../../../GoTvCommon/QtSource/ActivityReplyFileOffer.h \
    $$PWD/../../../GoTvCommon/QtSource/ActivityScanPeopleSearch.h \
    $$PWD/../../../GoTvCommon/QtSource/ActivityScanProfiles.h \
    $$PWD/../../../GoTvCommon/QtSource/ActivityScanStoryBoards.h \
    $$PWD/../../../GoTvCommon/QtSource/ActivityScanWebCams.h \
    $$PWD/../../../GoTvCommon/QtSource/ActivitySelectFileToSend.h \
    $$PWD/../../../GoTvCommon/QtSource/ActivitySessionFileOffer.h \
    $$PWD/../../../GoTvCommon/QtSource/ActivitySessionOptions.h \
    $$PWD/../../../GoTvCommon/QtSource/ActivityShowHelp.h \
    $$PWD/../../../GoTvCommon/QtSource/ActivitySnapShot.h \
    $$PWD/../../../GoTvCommon/QtSource/ActivitySoundOptions.h \
    $$PWD/../../../GoTvCommon/QtSource/ActivityStoryBoard.h \
    $$PWD/../../../GoTvCommon/QtSource/ActivityTimedMessage.h \
    $$PWD/../../../GoTvCommon/QtSource/ActivityToFriendBase.h \
    $$PWD/../../../GoTvCommon/QtSource/ActivityToFriendChangeFriendship.h \
    $$PWD/../../../GoTvCommon/QtSource/ActivityToFriendMultiSession.h \
    $$PWD/../../../GoTvCommon/QtSource/ActivityToFriendRequestRelay.h \
    $$PWD/../../../GoTvCommon/QtSource/ActivityToFriendTodGame.h \
    $$PWD/../../../GoTvCommon/QtSource/ActivityToFriendVideoPhone.h \
    $$PWD/../../../GoTvCommon/QtSource/ActivityToFriendViewSharedFiles.h \
    $$PWD/../../../GoTvCommon/QtSource/ActivityToFriendVoicePhone.h \
    $$PWD/../../../GoTvCommon/QtSource/ActivityUploads.h \
    $$PWD/../../../GoTvCommon/QtSource/ActivityVideoOptions.h \
    $$PWD/../../../GoTvCommon/QtSource/ActivityViewAudioFile.h \
    $$PWD/../../../GoTvCommon/QtSource/ActivityViewLibraryFiles.h \
    $$PWD/../../../GoTvCommon/QtSource/ActivityViewMySharedFiles.h \
    $$PWD/../../../GoTvCommon/QtSource/ActivityViewVideoFile.h \
    $$PWD/../../../GoTvCommon/QtSource/ActivityWebCamClient.h \
    $$PWD/../../../GoTvCommon/QtSource/ActivityBase.h \
    $$PWD/../../../GoTvCommon/QtSource/ActivityYesNoMsgBox.h \
    $$PWD/../../../GoTvCommon/QtSource/AssetFaceWidget.h \
    $$PWD/../../../GoTvCommon/QtSource/AssetPhotoWidget.h \
    $$PWD/../../../GoTvCommon/QtSource/AssetTextWidget.h \
    $$PWD/../../../GoTvCommon/QtSource/AssetVideoWidget.h \
    $$PWD/../../../GoTvCommon/QtSource/AssetVoiceWidget.h \
    $$PWD/../../../GoTvCommon/QtSource/AssetBaseWidget.h \
    $$PWD/../../../GoTvCommon/QtSource/AudioBuffer.h \
    $$PWD/../../../GoTvCommon/QtSource/AudioDefs.h \
    $$PWD/../../../GoTvCommon/QtSource/AudioDeviceCoreWin.h \
    $$PWD/../../../GoTvCommon/QtSource/AudioDeviceWaveWin.h \
    $$PWD/../../../GoTvCommon/QtSource/AudioMixerMgrWin.h \
    $$PWD/../../../GoTvCommon/QtSource/IVxWaveOut.h \
    $$PWD/../../../GoTvCommon/QtSource/VxWaveIn.h \
    $$PWD/../../../GoTvCommon/QtSource/VxWaveOut.h \
    $$PWD/../../../GoTvCommon/QtSource/VxWaveOutLinux.h \
    $$PWD/../../../GoTvCommon/QtSource/AudioOutQt.h \
    $$PWD/../../../GoTvCommon/QtSource/AudioTestGenerator.h \
    $$PWD/../../../GoTvCommon/QtSource/AudioOutIo.h \
    $$PWD/../../../GoTvCommon/QtSource/MyQtSoundInput.h \
    $$PWD/../../../GoTvCommon/QtSource/MyQtSoundOutput.h \
    $$PWD/../../../GoTvCommon/QtSource/MySndMgr.h \
    $$PWD/../../../GoTvCommon/QtSource/ShaderQt.h \
    $$PWD/../../../GoTvCommon/QtSource/VxResourceToRealFile.h \
    $$PWD/../../../GoTvCommon/QtSource/VxTilePositioner.h \
    $$PWD/../../../GoTvCommon/QtSource/AcceptCancelWidget.h \
    $$PWD/../../../GoTvCommon/QtSource/AvatarBar.h \
    $$PWD/../../../GoTvCommon/QtSource/BottomBarWidget.h \
    $$PWD/../../../GoTvCommon/QtSource/ImagePickBar.h \
    $$PWD/../../../GoTvCommon/QtSource/PlayerGlWidget.h \
    $$PWD/../../../GoTvCommon/QtSource/RenderGlWidget.h \
    $$PWD/../../../GoTvCommon/QtSource/RenderGlBaseWidget.h \
    $$PWD/../../../GoTvCommon/QtSource/RenderGlOffScreenSurface.h \
    $$PWD/../../../GoTvCommon/QtSource/VxAspectFrame.h \
    $$PWD/../../../GoTvCommon/QtSource/VxContextMenu.h \
    $$PWD/../../../GoTvCommon/QtSource/VxComboBox.h \
    $$PWD/../../../GoTvCommon/QtSource/ListEntryWidget.h \
    $$PWD/../../../GoTvCommon/QtSource/VxAvatarImage.h \
    $$PWD/../../../GoTvCommon/QtSource/VxPushButton.h \
    $$PWD/../../../GoTvCommon/QtSource/VxComboBoxFileFilter.h \
    $$PWD/../../../GoTvCommon/QtSource/VxGuidQt.h \
    $$PWD/../../../GoTvCommon/QtSource/VxLabel.h \
    $$PWD/../../../GoTvCommon/QtSource/VxMyFileInfo.h \
    $$PWD/../../../GoTvCommon/QtSource/VxSndInstance.h \
    $$PWD/../../../GoTvCommon/QtSource/VxFlatButton.h \
    $$PWD/../../../GoTvCommon/QtSource/VxFrame.h \
    $$PWD/../../../GoTvCommon/QtSource/VxMenuButton.h \
    $$PWD/../../../GoTvCommon/QtSource/VxMenuButtonBottom.h \
    $$PWD/../../../GoTvCommon/QtSource/VxMenuButtonTop.h \
    $$PWD/../../../GoTvCommon/QtSource/VxScrollArea.h \
    $$PWD/../../../GoTvCommon/QtSource/VxShredderButton.h \
    $$PWD/../../../GoTvCommon/QtSource/VxSpinProgress.h \
    $$PWD/../../../GoTvCommon/QtSource/VxTagLabel.h \
    $$PWD/../../../GoTvCommon/QtSource/VidWidget.h \
    $$PWD/../../../GoTvCommon/QtSource/VxWidgetBase.h \
    $$PWD/../../../GoTvCommon/QtSource/TodGameDefs.h \
    $$PWD/../../../GoTvCommon/QtSource/TodGameLogic.h \
    $$PWD/../../../GoTvCommon/QtSource/TodGameWidget.h \
    $$PWD/../../../GoTvCommon/QtSource/AppletMgr.h \
    $$PWD/../../../GoTvCommon/QtSource/AppletTheme.h \
    $$PWD/../../../GoTvCommon/QtSource/AppletRemoteControl.h \
    $$PWD/../../../GoTvCommon/QtSource/AppletSettings.h \
    $$PWD/../../../GoTvCommon/QtSource/AppletPlayerVideo.h \
    $$PWD/../../../GoTvCommon/QtSource/AppletPlayerBase.h \
    $$PWD/../../../GoTvCommon/QtSource/AppletBase.h \
    $$PWD/../../../GoTvCommon/QtSource/AppletKodi.h \
    $$PWD/../../../GoTvCommon/QtSource/AppletSharedContent.h \
    $$PWD/../../../GoTvCommon/QtSource/AppletUserIdentity.h \
    $$PWD/../../../GoTvCommon/QtSource/AppletLaunchPage.h \
    $$PWD/../../../GoTvCommon/QtSource/AppletLaunchWidget.h \
    $$PWD/../../../GoTvCommon/QtSource/KodiRun.h \
    $$PWD/../../../GoTvCommon/QtSource/AppDefs.h \
    $$PWD/../../../GoTvCommon/QtSource/AppGlobals.h \
    $$PWD/../../../GoTvCommon/QtSource/AppProfile.h \
    $$PWD/../../../GoTvCommon/QtSource/AppSettings.h \
    $$PWD/../../../GoTvCommon/QtSource/Constants.h \
    $$PWD/../../../GoTvCommon/QtSource/EventsQtToGoTv.h \
    $$PWD/../../../GoTvCommon/QtSource/KodiThread.h \
    $$PWD/../../../GoTvCommon/QtSource/MenuDefs.h \
    $$PWD/../../../GoTvCommon/QtSource/VxAppStyle.h \
    $$PWD/../../../GoTvCommon/QtSource/AppCommon.h \
    $$PWD/../../../GoTvCommon/QtSource/HomeWindow.h \
    $$PWD/../../../GoTvCommon/QtSource/VxAppTheme.h \
    $$PWD/../../../GoTvCommon/QtSource/VxAppDisplay.h \
    $$PWD/../../../../GoTvAppConfig.h \
    $$PWD/../../../../GoTvCompilerConfig.h \
    $$PWD/../../../../GoTvCpuArchDefines.h \
    $$PWD/../../../../GoTvDependLibrariesConfig.h \
    $$PWD/../../../../GoTvTargetOsConfig.h \
    $$PWD/../../AppSource/GoTvPlayerSettings.h \
    $$PWD/../../AppSource/exportdialog.h \
    $$PWD/../../AppSource/mainwindow.h \
    $$PWD/../../../../GoTvInterface/config_libgotvptop.h \
    $$PWD/../../../../GoTvInterface/GoTvRenderFrame.h \
    $$PWD/../../../../GoTvInterface/IDefs.h \
    $$PWD/../../../../GoTvInterface/IFromGui.h \
    $$PWD/../../../../GoTvInterface/IGoTv.h \
    $$PWD/../../../../GoTvInterface/IGoTvDefs.h \
    $$PWD/../../../../GoTvInterface/IGoTvRender.h \
    $$PWD/../../../../GoTvInterface/ILog.h \
    $$PWD/../../../../GoTvInterface/IScan.h \
    $$PWD/../../../../GoTvInterface/IToGui.h \
    $$PWD/../../../../GoTvInterface/OsWin32/IWin32.h \
    $$PWD/../../../../GoTvInterface/OsInterface/OsInterface.h

SOURCES += $$PWD/../../../GoTvCommon/QtSource/MessengerPage.cpp \
    $$PWD/../../../GoTvCommon/QtSource/VxDataHelper.cpp \
    $$PWD/../../../GoTvCommon/QtSource/DialogConfirmRemoveMessage.cpp \
    $$PWD/../../../GoTvCommon/QtSource/FileActionBarWidget.cpp \
    $$PWD/../../../GoTvCommon/QtSource/FileActionMenu.cpp \
    $$PWD/../../../GoTvCommon/QtSource/FileItemInfo.cpp \
    $$PWD/../../../GoTvCommon/QtSource/FileItemWidget.cpp \
    $$PWD/../../../GoTvCommon/QtSource/FileListReplySession.cpp \
    $$PWD/../../../GoTvCommon/QtSource/FileShareItemWidget.cpp \
    $$PWD/../../../GoTvCommon/QtSource/FileXferWidget.cpp \
    $$PWD/../../../GoTvCommon/QtSource/Friend.cpp \
    $$PWD/../../../GoTvCommon/QtSource/FriendList.cpp \
    $$PWD/../../../GoTvCommon/QtSource/FriendListDelegate.cpp \
    $$PWD/../../../GoTvCommon/QtSource/FriendListWidget.cpp \
    $$PWD/../../../GoTvCommon/QtSource/GuiFileActionSession.cpp \
    $$PWD/../../../GoTvCommon/QtSource/GuiFileXferSession.cpp \
    $$PWD/../../../GoTvCommon/QtSource/GuiHelpers.cpp \
    $$PWD/../../../GoTvCommon/QtSource/GuiOfferSession.cpp \
    $$PWD/../../../GoTvCommon/QtSource/HistoryEntryWidget.cpp \
    $$PWD/../../../GoTvCommon/QtSource/HistoryListWidget.cpp \
    $$PWD/../../../GoTvCommon/QtSource/IdentWidget.cpp \
    $$PWD/../../../GoTvCommon/QtSource/InstMsgWidget.cpp \
    $$PWD/../../../GoTvCommon/QtSource/MultiSessionState.cpp \
    $$PWD/../../../GoTvCommon/QtSource/MyIcons.cpp \
    $$PWD/../../../GoTvCommon/QtSource/OfferBarWidget.cpp \
    $$PWD/../../../GoTvCommon/QtSource/OfferSessionLogic.cpp \
    $$PWD/../../../GoTvCommon/QtSource/OfferSessionState.cpp \
    $$PWD/../../../GoTvCommon/QtSource/OffersMgr.cpp \
    $$PWD/../../../GoTvCommon/QtSource/OfferWidget.cpp \
    $$PWD/../../../GoTvCommon/QtSource/P2PThingFileMenu.cpp \
    $$PWD/../../../GoTvCommon/QtSource/P2PThingFileShare.cpp \
    $$PWD/../../../GoTvCommon/QtSource/P2PThingFriend.cpp \
    $$PWD/../../../GoTvCommon/QtSource/P2PThingLogin.cpp \
    $$PWD/../../../GoTvCommon/QtSource/P2PThingNotify.cpp \
    $$PWD/../../../GoTvCommon/QtSource/P2PThingOfferToFriend.cpp \
    $$PWD/../../../GoTvCommon/QtSource/P2PThingOptions.cpp \
    $$PWD/../../../GoTvCommon/QtSource/P2PThingScan.cpp \
    $$PWD/../../../GoTvCommon/QtSource/P2PThingSearch.cpp \
    $$PWD/../../../GoTvCommon/QtSource/P2PThingServers.cpp \
    $$PWD/../../../GoTvCommon/QtSource/P2PThingMedia.cpp \
    $$PWD/../../../GoTvCommon/QtSource/PopupMenu.cpp \
    $$PWD/../../../GoTvCommon/QtSource/PopupMenuDelegate.cpp \
    $$PWD/../../../GoTvCommon/QtSource/VxMenu.cpp \
    $$PWD/../../../GoTvCommon/QtSource/RasterWindow.cpp \
    $$PWD/../../../GoTvCommon/QtSource/SessionWidget.cpp \
    $$PWD/../../../GoTvCommon/QtSource/SoundCtrlWidget.cpp \
    $$PWD/../../../GoTvCommon/QtSource/StoryWidget.cpp \
    $$PWD/../../../GoTvCommon/QtSource/TextChatLogic.cpp \
    $$PWD/../../../GoTvCommon/QtSource/TitleBarWidget.cpp \
    $$PWD/../../../GoTvCommon/QtSource/ToGuiActivityClient.cpp \
    $$PWD/../../../GoTvCommon/QtSource/ToGuiFileXferClient.cpp \
    $$PWD/../../../GoTvCommon/QtSource/ToGuiHardwareCtrlClient.cpp \
    $$PWD/../../../GoTvCommon/QtSource/ChatEntryWidget.cpp \
    $$PWD/../../../GoTvCommon/QtSource/InputAllWidget.cpp \
    $$PWD/../../../GoTvCommon/QtSource/InputBaseWidget.cpp \
    $$PWD/../../../GoTvCommon/QtSource/InputFaceWidget.cpp \
    $$PWD/../../../GoTvCommon/QtSource/InputPhotoWidget.cpp \
    $$PWD/../../../GoTvCommon/QtSource/InputTextWidget.cpp \
    $$PWD/../../../GoTvCommon/QtSource/InputVideoWidget.cpp \
    $$PWD/../../../GoTvCommon/QtSource/InputVoiceWidget.cpp \
    $$PWD/../../../GoTvCommon/QtSource/ActivityAbout.cpp \
    $$PWD/../../../GoTvCommon/QtSource/ActivityAddRemoveLibraryFiles.cpp \
    $$PWD/../../../GoTvCommon/QtSource/ActivityAnchorSettings.cpp \
    $$PWD/../../../GoTvCommon/QtSource/ActivityBase.cpp \
    $$PWD/../../../GoTvCommon/QtSource/ActivityBrowseFiles.cpp \
    $$PWD/../../../GoTvCommon/QtSource/ActivityChooseIpPort.cpp \
    $$PWD/../../../GoTvCommon/QtSource/ActivityChooseTestWebsiteUrl.cpp \
    $$PWD/../../../GoTvCommon/QtSource/ActivityCreateProfile.cpp \
    $$PWD/../../../GoTvCommon/QtSource/ActivityDebugSettings.cpp \
    $$PWD/../../../GoTvCommon/QtSource/ActivityDownloadItemMenu.cpp \
    $$PWD/../../../GoTvCommon/QtSource/ActivityDownloads.cpp \
    $$PWD/../../../GoTvCommon/QtSource/ActivityEditAccount.cpp \
    $$PWD/../../../GoTvCommon/QtSource/ActivityEditProfile.cpp \
    $$PWD/../../../GoTvCommon/QtSource/ActivityFileSearch.cpp \
    $$PWD/../../../GoTvCommon/QtSource/ActivityIsPortOpenTest.cpp \
    $$PWD/../../../GoTvCommon/QtSource/ActivityManageAnchorSettings.cpp \
    $$PWD/../../../GoTvCommon/QtSource/ActivityMessageBox.cpp \
    $$PWD/../../../GoTvCommon/QtSource/ActivityNetServiceTest.cpp \
    $$PWD/../../../GoTvCommon/QtSource/ActivityNetworkSettings.cpp \
    $$PWD/../../../GoTvCommon/QtSource/ActivityNetworkState.cpp \
    $$PWD/../../../GoTvCommon/QtSource/ActivityPermissions.cpp \
    $$PWD/../../../GoTvCommon/QtSource/ActivityPermissionsRelay.cpp \
    $$PWD/../../../GoTvCommon/QtSource/ActivityPersonalRecorder.cpp \
    $$PWD/../../../GoTvCommon/QtSource/ActivityPhoneShake.cpp \
    $$PWD/../../../GoTvCommon/QtSource/ActivityReplyFileOffer.cpp \
    $$PWD/../../../GoTvCommon/QtSource/ActivityScanPeopleSearch.cpp \
    $$PWD/../../../GoTvCommon/QtSource/ActivityScanProfiles.cpp \
    $$PWD/../../../GoTvCommon/QtSource/ActivityScanStoryBoards.cpp \
    $$PWD/../../../GoTvCommon/QtSource/ActivityScanWebCams.cpp \
    $$PWD/../../../GoTvCommon/QtSource/ActivitySelectFileToSend.cpp \
    $$PWD/../../../GoTvCommon/QtSource/ActivitySessionFileOffer.cpp \
    $$PWD/../../../GoTvCommon/QtSource/ActivitySessionOptions.cpp \
    $$PWD/../../../GoTvCommon/QtSource/ActivityShowHelp.cpp \
    $$PWD/../../../GoTvCommon/QtSource/ActivitySnapShot.cpp \
    $$PWD/../../../GoTvCommon/QtSource/ActivitySoundOptions.cpp \
    $$PWD/../../../GoTvCommon/QtSource/ActivityStoryBoard.cpp \
    $$PWD/../../../GoTvCommon/QtSource/ActivityTimedMessage.cpp \
    $$PWD/../../../GoTvCommon/QtSource/ActivityToFriendBase.cpp \
    $$PWD/../../../GoTvCommon/QtSource/ActivityToFriendChangeFriendship.cpp \
    $$PWD/../../../GoTvCommon/QtSource/ActivityToFriendMultiSession.cpp \
    $$PWD/../../../GoTvCommon/QtSource/ActivityToFriendRequestRelay.cpp \
    $$PWD/../../../GoTvCommon/QtSource/ActivityToFriendTodGame.cpp \
    $$PWD/../../../GoTvCommon/QtSource/ActivityToFriendVideoPhone.cpp \
    $$PWD/../../../GoTvCommon/QtSource/ActivityToFriendViewSharedFiles.cpp \
    $$PWD/../../../GoTvCommon/QtSource/ActivityToFriendVoicePhone.cpp \
    $$PWD/../../../GoTvCommon/QtSource/ActivityUploads.cpp \
    $$PWD/../../../GoTvCommon/QtSource/ActivityVideoOptions.cpp \
    $$PWD/../../../GoTvCommon/QtSource/ActivityViewAudioFile.cpp \
    $$PWD/../../../GoTvCommon/QtSource/ActivityViewLibraryFiles.cpp \
    $$PWD/../../../GoTvCommon/QtSource/ActivityViewMySharedFiles.cpp \
    $$PWD/../../../GoTvCommon/QtSource/ActivityViewVideoFile.cpp \
    $$PWD/../../../GoTvCommon/QtSource/ActivityWebCamClient.cpp \
    $$PWD/../../../GoTvCommon/QtSource/ActivityYesNoMsgBox.cpp \
    $$PWD/../../../GoTvCommon/QtSource/AssetBaseWidget.cpp \
    $$PWD/../../../GoTvCommon/QtSource/AssetFaceWidget.cpp \
    $$PWD/../../../GoTvCommon/QtSource/AssetPhotoWidget.cpp \
    $$PWD/../../../GoTvCommon/QtSource/AssetTextWidget.cpp \
    $$PWD/../../../GoTvCommon/QtSource/AssetVideoWidget.cpp \
    $$PWD/../../../GoTvCommon/QtSource/AssetVoiceWidget.cpp \
    $$PWD/../../../GoTvCommon/QtSource/AudioBuffer.cpp \
    $$PWD/../../../GoTvCommon/QtSource/AudioDeviceCoreWin.cpp \
    $$PWD/../../../GoTvCommon/QtSource/AudioDeviceWaveWin.cpp \
    $$PWD/../../../GoTvCommon/QtSource/AudioMixerMgrWin.cpp \
    $$PWD/../../../GoTvCommon/QtSource/AudioOutIo.cpp \
    $$PWD/../../../GoTvCommon/QtSource/AudioOutQt.cpp \
    $$PWD/../../../GoTvCommon/QtSource/AudioTestGenerator.cpp \
    $$PWD/../../../GoTvCommon/QtSource/MyQtSoundInput.cpp \
    $$PWD/../../../GoTvCommon/QtSource/MyQtSoundOutput.cpp \
    $$PWD/../../../GoTvCommon/QtSource/MySndMgr.cpp \
    $$PWD/../../../GoTvCommon/QtSource/VxWaveIn.cpp \
    $$PWD/../../../GoTvCommon/QtSource/VxWaveOut.cpp \
    $$PWD/../../../GoTvCommon/QtSource/AcceptCancelWidget.cpp \
    $$PWD/../../../GoTvCommon/QtSource/AvatarBar.cpp \
    $$PWD/../../../GoTvCommon/QtSource/BottomBarWidget.cpp \
    $$PWD/../../../GoTvCommon/QtSource/ImagePickBar.cpp \
    $$PWD/../../../GoTvCommon/QtSource/PlayerGlWidget.cpp \
    $$PWD/../../../GoTvCommon/QtSource/RenderGlBaseWidget.cpp \
    $$PWD/../../../GoTvCommon/QtSource/RenderGlMatrix.cpp \
    $$PWD/../../../GoTvCommon/QtSource/RenderGlOffScreenSurface.cpp \
    $$PWD/../../../GoTvCommon/QtSource/RenderGlWidget.cpp \
    $$PWD/../../../GoTvCommon/QtSource/RenderGlWidgetFonts.cpp \
    $$PWD/../../../GoTvCommon/QtSource/RenderGlWidgetRender.cpp \
    $$PWD/../../../GoTvCommon/QtSource/RenderGlWidgetShaders.cpp \
    $$PWD/../../../GoTvCommon/QtSource/RenderGlWidgetTextures.cpp \
    $$PWD/../../../GoTvCommon/QtSource/ShaderQt.cpp \
    $$PWD/../../../GoTvCommon/QtSource/VxAspectFrame.cpp \
    $$PWD/../../../GoTvCommon/QtSource/VxComboBox.cpp \
    $$PWD/../../../GoTvCommon/QtSource/VxContextMenu.cpp \
    $$PWD/../../../GoTvCommon/QtSource/ListEntryWidget.cpp \
    $$PWD/../../../GoTvCommon/QtSource/VxAvatarImage.cpp \
    $$PWD/../../../GoTvCommon/QtSource/VxFrame.cpp \
    $$PWD/../../../GoTvCommon/QtSource/VxMenuButton.cpp \
    $$PWD/../../../GoTvCommon/QtSource/VxMenuButtonBottom.cpp \
    $$PWD/../../../GoTvCommon/QtSource/VxMenuButtonTop.cpp \
    $$PWD/../../../GoTvCommon/QtSource/VxPushButton.cpp \
    $$PWD/../../../GoTvCommon/QtSource/VxComboBoxFileFilter.cpp \
    $$PWD/../../../GoTvCommon/QtSource/VxFlatButton.cpp \
    $$PWD/../../../GoTvCommon/QtSource/VxGuidQt.cpp \
    $$PWD/../../../GoTvCommon/QtSource/VxLabel.cpp \
    $$PWD/../../../GoTvCommon/QtSource/VxMyFileInfo.cpp \
    $$PWD/../../../GoTvCommon/QtSource/VxSndInstance.cpp \
    $$PWD/../../../GoTvCommon/QtSource/VxResourceToRealFile.cpp \
    $$PWD/../../../GoTvCommon/QtSource/VxScrollArea.cpp \
    $$PWD/../../../GoTvCommon/QtSource/VxShredderButton.cpp \
    $$PWD/../../../GoTvCommon/QtSource/VxSpinProgress.cpp \
    $$PWD/../../../GoTvCommon/QtSource/VxTagLabel.cpp \
    $$PWD/../../../GoTvCommon/QtSource/VxTilePositioner.cpp \
    $$PWD/../../../GoTvCommon/QtSource/VidWidget.cpp \
    $$PWD/../../../GoTvCommon/QtSource/VxWidgetBase.cpp \
    $$PWD/../../../GoTvCommon/QtSource/TodGameDefs.cpp \
    $$PWD/../../../GoTvCommon/QtSource/TodGameLogic.cpp \
    $$PWD/../../../GoTvCommon/QtSource/TodGameWidget.cpp \
    $$PWD/../../../GoTvCommon/QtSource/AppletBase.cpp \
    $$PWD/../../../GoTvCommon/QtSource/AppletKodi.cpp \
    $$PWD/../../../GoTvCommon/QtSource/AppletMgr.cpp \
    $$PWD/../../../GoTvCommon/QtSource/AppletPlayerBase.cpp \
    $$PWD/../../../GoTvCommon/QtSource/AppletRemoteControl.cpp \
    $$PWD/../../../GoTvCommon/QtSource/AppletSettings.cpp \
    $$PWD/../../../GoTvCommon/QtSource/AppletSharedContent.cpp \
    $$PWD/../../../GoTvCommon/QtSource/AppletTheme.cpp \
    $$PWD/../../../GoTvCommon/QtSource/AppletPlayerVideo.cpp \
    $$PWD/../../../GoTvCommon/QtSource/AppletUserIdentity.cpp \
    $$PWD/../../../GoTvCommon/QtSource/AppletLaunchWidget.cpp \
    $$PWD/../../../GoTvCommon/QtSource/AppletLaunchPage.cpp \
    $$PWD/../../../GoTvCommon/QtSource/AppCommon.cpp \
    $$PWD/../../../GoTvCommon/QtSource/AppCommonAudio.cpp \
    $$PWD/../../../GoTvCommon/QtSource/AppCommonEvents.cpp \
    $$PWD/../../../GoTvCommon/QtSource/AppCommonLogin.cpp \
    $$PWD/../../../GoTvCommon/QtSource/AppCommonRender.cpp \
    $$PWD/../../../GoTvCommon/QtSource/AppDefs.cpp \
    $$PWD/../../../GoTvCommon/QtSource/AppGlobals.cpp \
    $$PWD/../../../GoTvCommon/QtSource/AppProfile.cpp \
    $$PWD/../../../GoTvCommon/QtSource/AppSettings.cpp \
    $$PWD/../../../GoTvCommon/QtSource/Constants.cpp \
    $$PWD/../../../GoTvCommon/QtSource/EventsQtToGoTv.cpp \
    $$PWD/../../../GoTvCommon/QtSource/KodiThread.cpp \
    $$PWD/../../../GoTvCommon/QtSource/VxAppStyle.cpp \
    $$PWD/../../../GoTvCommon/QtSource/VxAppTheme.cpp \
    $$PWD/../../../GoTvCommon/QtSource/HomeWindow.cpp \
    $$PWD/../../../GoTvCommon/QtSource/VxAppDisplay.cpp \
    $$PWD/../../AppSource/exportdialog.cpp \
    $$PWD/../../AppSource/GoTvPlayerSettings.cpp \
    $$PWD/../../AppSource/main.cpp \
    $$PWD/../../AppSource/mainwindow.cpp \
    $$PWD/../../../../GoTvInterface/GoTvRenderFrame.cpp \
    $$PWD/../../../../GoTvInterface/IGoTv.cpp \
    $$PWD/../../../../GoTvInterface/IGoTvFromGui.cpp \
    $$PWD/../../../../GoTvInterface/IGoTvRender.cpp \
    $$PWD/../../../../GoTvInterface/IGoTvToGui.cpp \
    $$PWD/../../../../GoTvInterface/ILog.cpp \
    $$PWD/../../../../GoTvInterface/IToGui.cpp \
    $$PWD/../../../../GoTvInterface/OsWin32/IWin32.cpp \
    $$PWD/../../../../GoTvInterface/OsInterface/OsInterface.cpp
FORMS += $$PWD/../../../GoTvCommon/Forms/ActivityAbout.ui \
    $$PWD/../../../GoTvCommon/Forms/ActivityAddRemoveLibraryFiles.ui \
    $$PWD/../../../GoTvCommon/Forms/ActivityAnchorSettings.ui \
    $$PWD/../../../GoTvCommon/Forms/ActivityBrowseFiles.ui \
    $$PWD/../../../GoTvCommon/Forms/ActivityChooseIpAddress.ui \
    $$PWD/../../../GoTvCommon/Forms/ActivityChooseIpPort.ui \
    $$PWD/../../../GoTvCommon/Forms/ActivityChooseTestWebsiteUrl.ui \
    $$PWD/../../../GoTvCommon/Forms/ActivityConnectionOptions.ui \
    $$PWD/../../../GoTvCommon/Forms/ActivityCreateProfile.ui \
    $$PWD/../../../GoTvCommon/Forms/ActivityDebugSettings.ui \
    $$PWD/../../../GoTvCommon/Forms/ActivityDownloadItemMenu.ui \
    $$PWD/../../../GoTvCommon/Forms/ActivityDownloads.ui \
    $$PWD/../../../GoTvCommon/Forms/ActivityEditAccount.ui \
    $$PWD/../../../GoTvCommon/Forms/ActivityEditProfile.ui \
    $$PWD/../../../GoTvCommon/Forms/ActivityFileSearch.ui \
    $$PWD/../../../GoTvCommon/Forms/ActivityIsPortOpenTest.ui \
    $$PWD/../../../GoTvCommon/Forms/ActivityManageAnchorSettings.ui \
    $$PWD/../../../GoTvCommon/Forms/ActivityMessageBox.ui \
    $$PWD/../../../GoTvCommon/Forms/ActivityNetServiceTest.ui \
    $$PWD/../../../GoTvCommon/Forms/ActivityNetworkSettings.ui \
    $$PWD/../../../GoTvCommon/Forms/ActivityNetworkStartupTest.ui \
    $$PWD/../../../GoTvCommon/Forms/ActivityNetworkStatus.ui \
    $$PWD/../../../GoTvCommon/Forms/ActivityNetworkTest.ui \
    $$PWD/../../../GoTvCommon/Forms/ActivityPermissions.ui \
    $$PWD/../../../GoTvCommon/Forms/ActivityPermissionsRelay.ui \
    $$PWD/../../../GoTvCommon/Forms/ActivityPersonalRecorder.ui \
    $$PWD/../../../GoTvCommon/Forms/ActivityPhoneShake.ui \
    $$PWD/../../../GoTvCommon/Forms/ActivityReplyFileOffer.ui \
    $$PWD/../../../GoTvCommon/Forms/ActivityScanPeopleSearch.ui \
    $$PWD/../../../GoTvCommon/Forms/ActivityScanProfiles.ui \
    $$PWD/../../../GoTvCommon/Forms/ActivityScanStoryBoards.ui \
    $$PWD/../../../GoTvCommon/Forms/ActivityScanWebCams.ui \
    $$PWD/../../../GoTvCommon/Forms/ActivitySelectFileToSend.ui \
    $$PWD/../../../GoTvCommon/Forms/ActivitySessionFileOffer.ui \
    $$PWD/../../../GoTvCommon/Forms/ActivitySessionOptions.ui \
    $$PWD/../../../GoTvCommon/Forms/ActivityShowHelp.ui \
    $$PWD/../../../GoTvCommon/Forms/ActivitySnapShot.ui \
    $$PWD/../../../GoTvCommon/Forms/ActivitySoundOptions.ui \
    $$PWD/../../../GoTvCommon/Forms/ActivityStoryBoard.ui \
    $$PWD/../../../GoTvCommon/Forms/ActivityTimedMessage.ui \
    $$PWD/../../../GoTvCommon/Forms/ActivityToFriendBase.ui \
    $$PWD/../../../GoTvCommon/Forms/ActivityToFriendChangeFriendship.ui \
    $$PWD/../../../GoTvCommon/Forms/ActivityToFriendMultiSession.ui \
    $$PWD/../../../GoTvCommon/Forms/ActivityToFriendOfferFile.ui \
    $$PWD/../../../GoTvCommon/Forms/ActivityToFriendRequestRelay.ui \
    $$PWD/../../../GoTvCommon/Forms/ActivityToFriendTodGame.ui \
    $$PWD/../../../GoTvCommon/Forms/ActivityToFriendVideoPhone.ui \
    $$PWD/../../../GoTvCommon/Forms/ActivityToFriendViewSharedFiles.ui \
    $$PWD/../../../GoTvCommon/Forms/ActivityToFriendVoicePhone.ui \
    $$PWD/../../../GoTvCommon/Forms/ActivityTruthOrDare.ui \
    $$PWD/../../../GoTvCommon/Forms/ActivityUploads.ui \
    $$PWD/../../../GoTvCommon/Forms/ActivityVideoOptions.ui \
    $$PWD/../../../GoTvCommon/Forms/ActivityViewAudioFile.ui \
    $$PWD/../../../GoTvCommon/Forms/ActivityViewLibraryFiles.ui \
    $$PWD/../../../GoTvCommon/Forms/ActivityViewLog.ui \
    $$PWD/../../../GoTvCommon/Forms/ActivityViewMySharedFiles.ui \
    $$PWD/../../../GoTvCommon/Forms/ActivityViewVideoFile.ui \
    $$PWD/../../../GoTvCommon/Forms/ActivityWebCamClient.ui \
    $$PWD/../../../GoTvCommon/Forms/ActivityYesNo.ui \
    $$PWD/../../../GoTvCommon/Forms/AssetFaceWidget.ui \
    $$PWD/../../../GoTvCommon/Forms/AssetPhotoWidget.ui \
    $$PWD/../../../GoTvCommon/Forms/AssetTextWidget.ui \
    $$PWD/../../../GoTvCommon/Forms/AssetVideoWidget.ui \
    $$PWD/../../../GoTvCommon/Forms/AssetVoiceWidget.ui \
    $$PWD/../../../GoTvCommon/Forms/AvatarBarWidget.ui \
    $$PWD/../../../GoTvCommon/Forms/CentralFrame.ui \
    $$PWD/../../../GoTvCommon/Forms/CentralWidget.ui \
    $$PWD/../../../GoTvCommon/Forms/ChatEntryWidget.ui \
    $$PWD/../../../GoTvCommon/Forms/DialogConfirmRemoveMessage.ui \
    $$PWD/../../../GoTvCommon/Forms/FileActionBarWidget.ui \
    $$PWD/../../../GoTvCommon/Forms/FileActionMenu.ui \
    $$PWD/../../../GoTvCommon/Forms/FileDisplayWidget.ui \
    $$PWD/../../../GoTvCommon/Forms/FileItemWidget.ui \
    $$PWD/../../../GoTvCommon/Forms/FileShareItemWidget.ui \
    $$PWD/../../../GoTvCommon/Forms/FileXferWidget.ui \
    $$PWD/../../../GoTvCommon/Forms/FriendListDlg.ui \
    $$PWD/../../../GoTvCommon/Forms/HistoryEntryWidget.ui \
    $$PWD/../../../GoTvCommon/Forms/IdentWidget.ui \
    $$PWD/../../../GoTvCommon/Forms/InputAllWidget.ui \
    $$PWD/../../../GoTvCommon/Forms/InputFaceWidget.ui \
    $$PWD/../../../GoTvCommon/Forms/InputPhotoWidget.ui \
    $$PWD/../../../GoTvCommon/Forms/InputTextWidget.ui \
    $$PWD/../../../GoTvCommon/Forms/InputVideoWidget.ui \
    $$PWD/../../../GoTvCommon/Forms/InputVoiceWidget.ui \
    $$PWD/../../../GoTvCommon/Forms/InstMsgWidget.ui \
    $$PWD/../../../GoTvCommon/Forms/ListEntryWidget.ui \
    $$PWD/../../../GoTvCommon/Forms/OfferBarWidget.ui \
    $$PWD/../../../GoTvCommon/Forms/OfferWidget.ui \
    $$PWD/../../../GoTvCommon/Forms/PopupMenuWidget.ui \
    $$PWD/../../../GoTvCommon/Forms/SessionWidget.ui \
    $$PWD/../../../GoTvCommon/Forms/SoundCtrlWidget.ui \
    $$PWD/../../../GoTvCommon/Forms/StoryWidget.ui \
    $$PWD/../../../GoTvCommon/Forms/TitleBarWidget.ui \
    $$PWD/../../../GoTvCommon/Forms/TodGameWidget.ui \
    $$PWD/../../../GoTvCommon/Forms/VidWidget.ui \
    $$PWD/../../../GoTvCommon/Forms/HomeWindow.ui \
    $$PWD/../../../GoTvCommon/Forms/AppletLaunchWidget.ui \
    $$PWD/../../../GoTvCommon/Forms/BottomBarWidget.ui \
    $$PWD/../../../GoTvCommon/Forms/ActivityBase.ui \
    $$PWD/../../../GoTvCommon/Forms/AppletTheme.ui \
    $$PWD/../../../GoTvCommon/Forms/AcceptCancelWidget.ui \
    $$PWD/../../../GoTvCommon/Forms/AppletSettings.ui \
    $$PWD/../../../GoTvCommon/Forms/AppletPlayerVideo.ui \
    $$PWD/../../../GoTvCommon/Forms/ImagePickBar.ui \
    $$PWD/../../../GoTvCommon/Forms/AppletKodi.ui \
    $$PWD/../../../GoTvCommon/Forms/AppletSharedContent.ui \
    $$PWD/../../../GoTvCommon/Forms/AppletUserIdentity.ui \
    $$PWD/../../../GoTvCommon/Forms/PlayerGlWidget.ui
RESOURCES += $$PWD/../../../GoTvCommon/gotvcommon.qrc
