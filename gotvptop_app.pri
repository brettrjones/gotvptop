message("Building GoTvPtoP")

INCLUDEPATH += $$PWD/
INCLUDEPATH += $$PWD/GoTvCore


FORMS += $$PWD/GoTvApps/GoTvCommon/Forms/ActivityAbout.ui \
    $$PWD/GoTvApps/GoTvCommon/Forms/ActivityAddRemoveLibraryFiles.ui \
    $$PWD/GoTvApps/GoTvCommon/Forms/ActivityAnchorSettings.ui \
    $$PWD/GoTvApps/GoTvCommon/Forms/ActivityBrowseFiles.ui \
    $$PWD/GoTvApps/GoTvCommon/Forms/ActivityChooseIpAddress.ui \
    $$PWD/GoTvApps/GoTvCommon/Forms/ActivityChooseIpPort.ui \
    $$PWD/GoTvApps/GoTvCommon/Forms/ActivityChooseTestWebsiteUrl.ui \
    $$PWD/GoTvApps/GoTvCommon/Forms/ActivityConnectionOptions.ui \
    $$PWD/GoTvApps/GoTvCommon/Forms/ActivityCreateProfile.ui \
    $$PWD/GoTvApps/GoTvCommon/Forms/ActivityDebugSettings.ui \
    $$PWD/GoTvApps/GoTvCommon/Forms/ActivityDownloadItemMenu.ui \
    $$PWD/GoTvApps/GoTvCommon/Forms/ActivityDownloads.ui \
    $$PWD/GoTvApps/GoTvCommon/Forms/ActivityEditAccount.ui \
    $$PWD/GoTvApps/GoTvCommon/Forms/ActivityEditProfile.ui \
    $$PWD/GoTvApps/GoTvCommon/Forms/ActivityFileSearch.ui \
    $$PWD/GoTvApps/GoTvCommon/Forms/ActivityIsPortOpenTest.ui \
    $$PWD/GoTvApps/GoTvCommon/Forms/ActivityManageAnchorSettings.ui \
    $$PWD/GoTvApps/GoTvCommon/Forms/ActivityMessageBox.ui \
    $$PWD/GoTvApps/GoTvCommon/Forms/ActivityNetServiceTest.ui \
    $$PWD/GoTvApps/GoTvCommon/Forms/ActivityNetworkSettings.ui \
    $$PWD/GoTvApps/GoTvCommon/Forms/ActivityNetworkStartupTest.ui \
    $$PWD/GoTvApps/GoTvCommon/Forms/ActivityNetworkStatus.ui \
    $$PWD/GoTvApps/GoTvCommon/Forms/ActivityNetworkTest.ui \
    $$PWD/GoTvApps/GoTvCommon/Forms/ActivityPermissions.ui \
    $$PWD/GoTvApps/GoTvCommon/Forms/ActivityPermissionsRelay.ui \
    $$PWD/GoTvApps/GoTvCommon/Forms/ActivityPersonalRecorder.ui \
    $$PWD/GoTvApps/GoTvCommon/Forms/ActivityPhoneShake.ui \
    $$PWD/GoTvApps/GoTvCommon/Forms/ActivityReplyFileOffer.ui \
    $$PWD/GoTvApps/GoTvCommon/Forms/ActivityScanPeopleSearch.ui \
    $$PWD/GoTvApps/GoTvCommon/Forms/ActivityScanProfiles.ui \
    $$PWD/GoTvApps/GoTvCommon/Forms/ActivityScanStoryBoards.ui \
    $$PWD/GoTvApps/GoTvCommon/Forms/ActivityScanWebCams.ui \
    $$PWD/GoTvApps/GoTvCommon/Forms/ActivitySelectFileToSend.ui \
    $$PWD/GoTvApps/GoTvCommon/Forms/ActivitySessionFileOffer.ui \
    $$PWD/GoTvApps/GoTvCommon/Forms/ActivitySessionOptions.ui \
    $$PWD/GoTvApps/GoTvCommon/Forms/ActivityShowHelp.ui \
    $$PWD/GoTvApps/GoTvCommon/Forms/ActivitySnapShot.ui \
    $$PWD/GoTvApps/GoTvCommon/Forms/ActivitySoundOptions.ui \
    $$PWD/GoTvApps/GoTvCommon/Forms/ActivityStoryBoard.ui \
    $$PWD/GoTvApps/GoTvCommon/Forms/ActivityTimedMessage.ui \
    $$PWD/GoTvApps/GoTvCommon/Forms/ActivityToFriendBase.ui \
    $$PWD/GoTvApps/GoTvCommon/Forms/ActivityToFriendChangeFriendship.ui \
    $$PWD/GoTvApps/GoTvCommon/Forms/ActivityToFriendMultiSession.ui \
    $$PWD/GoTvApps/GoTvCommon/Forms/ActivityToFriendOfferFile.ui \
    $$PWD/GoTvApps/GoTvCommon/Forms/ActivityToFriendRequestRelay.ui \
    $$PWD/GoTvApps/GoTvCommon/Forms/ActivityToFriendTodGame.ui \
    $$PWD/GoTvApps/GoTvCommon/Forms/ActivityToFriendVideoPhone.ui \
    $$PWD/GoTvApps/GoTvCommon/Forms/ActivityToFriendViewSharedFiles.ui \
    $$PWD/GoTvApps/GoTvCommon/Forms/ActivityToFriendVoicePhone.ui \
    $$PWD/GoTvApps/GoTvCommon/Forms/ActivityTruthOrDare.ui \
    $$PWD/GoTvApps/GoTvCommon/Forms/ActivityUploads.ui \
    $$PWD/GoTvApps/GoTvCommon/Forms/ActivityVideoOptions.ui \
    $$PWD/GoTvApps/GoTvCommon/Forms/ActivityViewAudioFile.ui \
    $$PWD/GoTvApps/GoTvCommon/Forms/ActivityViewLibraryFiles.ui \
    $$PWD/GoTvApps/GoTvCommon/Forms/ActivityViewLog.ui \
    $$PWD/GoTvApps/GoTvCommon/Forms/ActivityViewMySharedFiles.ui \
    $$PWD/GoTvApps/GoTvCommon/Forms/ActivityViewVideoFile.ui \
    $$PWD/GoTvApps/GoTvCommon/Forms/ActivityWebCamClient.ui \
    $$PWD/GoTvApps/GoTvCommon/Forms/ActivityYesNo.ui \
    $$PWD/GoTvApps/GoTvCommon/Forms/AssetFaceWidget.ui \
    $$PWD/GoTvApps/GoTvCommon/Forms/AssetPhotoWidget.ui \
    $$PWD/GoTvApps/GoTvCommon/Forms/AssetTextWidget.ui \
    $$PWD/GoTvApps/GoTvCommon/Forms/AssetVideoWidget.ui \
    $$PWD/GoTvApps/GoTvCommon/Forms/AssetVoiceWidget.ui \
    $$PWD/GoTvApps/GoTvCommon/Forms/AvatarBarWidget.ui \
    $$PWD/GoTvApps/GoTvCommon/Forms/CentralFrame.ui \
    $$PWD/GoTvApps/GoTvCommon/Forms/CentralWidget.ui \
    $$PWD/GoTvApps/GoTvCommon/Forms/ChatEntryWidget.ui \
    $$PWD/GoTvApps/GoTvCommon/Forms/DialogConfirmRemoveMessage.ui \
    $$PWD/GoTvApps/GoTvCommon/Forms/FileActionBarWidget.ui \
    $$PWD/GoTvApps/GoTvCommon/Forms/FileActionMenu.ui \
    $$PWD/GoTvApps/GoTvCommon/Forms/FileDisplayWidget.ui \
    $$PWD/GoTvApps/GoTvCommon/Forms/FileItemWidget.ui \
    $$PWD/GoTvApps/GoTvCommon/Forms/FileShareItemWidget.ui \
    $$PWD/GoTvApps/GoTvCommon/Forms/FileXferWidget.ui \
    $$PWD/GoTvApps/GoTvCommon/Forms/FriendListDlg.ui \
    $$PWD/GoTvApps/GoTvCommon/Forms/HistoryEntryWidget.ui \
    $$PWD/GoTvApps/GoTvCommon/Forms/IdentWidget.ui \
    $$PWD/GoTvApps/GoTvCommon/Forms/InputAllWidget.ui \
    $$PWD/GoTvApps/GoTvCommon/Forms/InputFaceWidget.ui \
    $$PWD/GoTvApps/GoTvCommon/Forms/InputPhotoWidget.ui \
    $$PWD/GoTvApps/GoTvCommon/Forms/InputTextWidget.ui \
    $$PWD/GoTvApps/GoTvCommon/Forms/InputVideoWidget.ui \
    $$PWD/GoTvApps/GoTvCommon/Forms/InputVoiceWidget.ui \
    $$PWD/GoTvApps/GoTvCommon/Forms/InstMsgWidget.ui \
    $$PWD/GoTvApps/GoTvCommon/Forms/ListEntryWidget.ui \
    $$PWD/GoTvApps/GoTvCommon/Forms/OfferBarWidget.ui \
    $$PWD/GoTvApps/GoTvCommon/Forms/OfferWidget.ui \
    $$PWD/GoTvApps/GoTvCommon/Forms/PopupMenuWidget.ui \
    $$PWD/GoTvApps/GoTvCommon/Forms/SessionWidget.ui \
    $$PWD/GoTvApps/GoTvCommon/Forms/SoundCtrlWidget.ui \
    $$PWD/GoTvApps/GoTvCommon/Forms/StoryWidget.ui \
    $$PWD/GoTvApps/GoTvCommon/Forms/TitleBarWidget.ui \
    $$PWD/GoTvApps/GoTvCommon/Forms/TodGameWidget.ui \
    $$PWD/GoTvApps/GoTvCommon/Forms/VidWidget.ui \
    $$PWD/GoTvApps/GoTvCommon/Forms/HomeWindow.ui \
    $$PWD/GoTvApps/GoTvCommon/Forms/AppletLaunchWidget.ui \
    $$PWD/GoTvApps/GoTvCommon/Forms/BottomBarWidget.ui \
    $$PWD/GoTvApps/GoTvCommon/Forms/ActivityBase.ui \
    $$PWD/GoTvApps/GoTvCommon/Forms/AppletTheme.ui \
    $$PWD/GoTvApps/GoTvCommon/Forms/AcceptCancelWidget.ui \
    $$PWD/GoTvApps/GoTvCommon/Forms/AppletSettings.ui \
    $$PWD/GoTvApps/GoTvCommon/Forms/AppletPlayerVideo.ui \
    $$PWD/GoTvApps/GoTvCommon/Forms/ImagePickBar.ui \
    $$PWD/GoTvApps/GoTvCommon/Forms/AppletKodi.ui \
    $$PWD/GoTvApps/GoTvCommon/Forms/AppletSharedContent.ui \
    $$PWD/GoTvApps/GoTvCommon/Forms/AppletUserIdentity.ui \
    $$PWD/GoTvApps/GoTvCommon/Forms/PlayerGlWidget.ui


HEADERS += $$PWD/GoTvApps/GoTvCommon/QtSource/MyIconsDefs.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/VxDataHelper.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/FileItemInfo.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/Friend.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/FriendList.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/FriendListDelegate.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/GuiFileXferSession.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/GuiHelpers.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/MyIcons.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/OfferSessionCallbackInterface.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/OfferSessionLogic.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/OfferSessionState.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/PopupMenuDelegate.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/SoundDefs.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ToGuiActivityClient.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ToGuiActivityInterface.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ToGuiFileXferClient.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ToGuiFileXferInterface.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ToGuiHardwareControlInterface.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ToGuiHardwareCtrlClient.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ToGuiOfferInterface.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/UserProfile.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/AnalogClock.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/MessengerPage.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/DialogConfirmRemoveMessage.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/FileActionBarWidget.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/FileActionMenu.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/FileItemWidget.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/FileListReplySession.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/FileShareItemWidget.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/FileXferWidget.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/FriendListWidget.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/GuiFileActionSession.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/GuiOfferSession.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/HistoryEntryWidget.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/HistoryListWidget.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/IdentWidget.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/InstMsgWidget.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/MultiSessionState.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/TitleBarWidget.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/OfferBarWidget.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/OffersMgr.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/OfferWidget.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/PopupMenu.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/VxMenu.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/SessionWidget.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/SoundCtrlWidget.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/StoryWidget.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/TextChatLogic.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/RasterWindow.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ChatEntryWidget.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/InputAllWidget.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/InputBaseWidget.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/InputFaceWidget.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/InputPhotoWidget.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/InputTextWidget.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/InputVideoWidget.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/InputVoiceWidget.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ActivityAbout.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ActivityAddRemoveLibraryFiles.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ActivityAnchorSettings.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ActivityBrowseFiles.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ActivityChooseIpPort.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ActivityChooseTestWebsiteUrl.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ActivityCreateProfile.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ActivityDebugSettings.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ActivityDownloadItemMenu.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ActivityDownloads.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ActivityEditAccount.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ActivityEditProfile.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ActivityFileSearch.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ActivityIsPortOpenTest.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ActivityManageAnchorSettings.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ActivityMessageBox.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ActivityNetServiceTest.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ActivityNetworkSettings.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ActivityNetworkState.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ActivityPermissions.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ActivityPermissionsRelay.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ActivityPersonalRecorder.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ActivityPhoneShake.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ActivityReplyFileOffer.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ActivityScanPeopleSearch.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ActivityScanProfiles.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ActivityScanStoryBoards.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ActivityScanWebCams.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ActivitySelectFileToSend.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ActivitySessionFileOffer.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ActivitySessionOptions.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ActivityShowHelp.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ActivitySnapShot.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ActivitySoundOptions.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ActivityStoryBoard.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ActivityTimedMessage.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ActivityToFriendBase.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ActivityToFriendChangeFriendship.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ActivityToFriendMultiSession.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ActivityToFriendRequestRelay.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ActivityToFriendTodGame.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ActivityToFriendVideoPhone.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ActivityToFriendViewSharedFiles.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ActivityToFriendVoicePhone.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ActivityUploads.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ActivityVideoOptions.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ActivityViewAudioFile.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ActivityViewLibraryFiles.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ActivityViewMySharedFiles.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ActivityViewVideoFile.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ActivityWebCamClient.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ActivityBase.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ActivityYesNoMsgBox.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/AssetFaceWidget.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/AssetPhotoWidget.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/AssetTextWidget.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/AssetVideoWidget.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/AssetVoiceWidget.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/AssetBaseWidget.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/AudioBuffer.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/AudioDefs.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/AudioDeviceCoreWin.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/AudioDeviceWaveWin.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/AudioMixerMgrWin.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/IVxWaveOut.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/VxWaveIn.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/VxWaveOut.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/VxWaveOutLinux.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/AudioOutQt.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/AudioTestGenerator.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/AudioOutIo.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/MyQtSoundInput.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/MyQtSoundOutput.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/MySndMgr.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ShaderQt.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/VxResourceToRealFile.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/VxTilePositioner.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/AcceptCancelWidget.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/AvatarBar.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/BottomBarWidget.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ImagePickBar.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/PlayerGlWidget.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/RenderGlWidget.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/RenderGlBaseWidget.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/RenderGlOffScreenSurface.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/VxAspectFrame.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/VxContextMenu.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/VxComboBox.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ListEntryWidget.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/VxAvatarImage.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/VxPushButton.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/VxComboBoxFileFilter.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/VxGuidQt.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/VxLabel.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/VxMyFileInfo.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/VxSndInstance.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/VxFlatButton.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/VxFrame.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/VxMenuButton.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/VxMenuButtonBottom.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/VxMenuButtonTop.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/VxScrollArea.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/VxShredderButton.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/VxSpinProgress.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/VxTagLabel.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/VidWidget.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/VxWidgetBase.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/TodGameDefs.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/TodGameLogic.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/TodGameWidget.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/AppletMgr.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/AppletTheme.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/AppletRemoteControl.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/AppletSettings.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/AppletPlayerVideo.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/AppletPlayerBase.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/AppletBase.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/AppletKodi.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/AppletSharedContent.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/AppletUserIdentity.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/AppletLaunchPage.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/AppletLaunchWidget.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/KodiRun.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/AppDefs.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/AppGlobals.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/AppProfile.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/AppSettings.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/Constants.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/EventsQtToGoTv.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/KodiThread.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/MenuDefs.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/VxAppStyle.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/AppCommon.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/HomeWindow.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/VxAppTheme.h \
    $$PWD/GoTvApps/GoTvCommon/QtSource/VxAppDisplay.h \
    $$PWD/GoTvAppConfig.h \
    $$PWD/GoTvCompilerConfig.h \
    $$PWD/GoTvCpuArchDefines.h \
    $$PWD/GoTvDependLibrariesConfig.h \
    $$PWD/GoTvTargetOsConfig.h \
    $$PWD/GoTvApps/GoTvPtoP/AppSource/GoTvPlayerSettings.h \
    $$PWD/GoTvInterface/config_libgotvptop.h \
    $$PWD/GoTvInterface/GoTvRenderFrame.h \
    $$PWD/GoTvInterface/IDefs.h \
    $$PWD/GoTvInterface/IFromGui.h \
    $$PWD/GoTvInterface/IGoTv.h \
    $$PWD/GoTvInterface/IGoTvDefs.h \
    $$PWD/GoTvInterface/IGoTvRender.h \
    $$PWD/GoTvInterface/ILog.h \
    $$PWD/GoTvInterface/IScan.h \
    $$PWD/GoTvInterface/IToGui.h \
    $$PWD/GoTvInterface/OsInterface/OsInterface.h \
    $$PWD/GoTvInterface/OsWin32/IWin32.h \
    $$PWD/GoTvInterface/OsLinux/ILinux.h \
    $$PWD/GoTvInterface/OsAndroid/IAndroid.h \
    $$PWD/GoTvApps/GoTvPtoP/AppSource/exportdialog.h

SOURCES += $$PWD/GoTvApps/GoTvCommon/QtSource/MessengerPage.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/VxDataHelper.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/DialogConfirmRemoveMessage.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/FileActionBarWidget.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/FileActionMenu.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/FileItemInfo.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/FileItemWidget.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/FileListReplySession.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/FileShareItemWidget.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/FileXferWidget.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/Friend.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/FriendList.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/FriendListDelegate.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/FriendListWidget.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/GuiFileActionSession.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/GuiFileXferSession.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/GuiHelpers.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/GuiOfferSession.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/HistoryEntryWidget.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/HistoryListWidget.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/IdentWidget.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/InstMsgWidget.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/MultiSessionState.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/MyIcons.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/OfferBarWidget.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/OfferSessionLogic.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/OfferSessionState.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/OffersMgr.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/OfferWidget.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/P2PThingFileMenu.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/P2PThingFileShare.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/P2PThingFriend.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/P2PThingLogin.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/P2PThingNotify.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/P2PThingOfferToFriend.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/P2PThingOptions.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/P2PThingScan.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/P2PThingSearch.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/P2PThingServers.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/P2PThingMedia.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/PopupMenu.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/PopupMenuDelegate.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/VxMenu.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/RasterWindow.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/SessionWidget.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/SoundCtrlWidget.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/StoryWidget.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/TextChatLogic.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/TitleBarWidget.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ToGuiActivityClient.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ToGuiFileXferClient.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ToGuiHardwareCtrlClient.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ChatEntryWidget.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/InputAllWidget.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/InputBaseWidget.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/InputFaceWidget.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/InputPhotoWidget.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/InputTextWidget.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/InputVideoWidget.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/InputVoiceWidget.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ActivityAbout.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ActivityAddRemoveLibraryFiles.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ActivityAnchorSettings.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ActivityBase.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ActivityBrowseFiles.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ActivityChooseIpPort.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ActivityChooseTestWebsiteUrl.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ActivityCreateProfile.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ActivityDebugSettings.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ActivityDownloadItemMenu.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ActivityDownloads.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ActivityEditAccount.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ActivityEditProfile.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ActivityFileSearch.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ActivityIsPortOpenTest.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ActivityManageAnchorSettings.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ActivityMessageBox.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ActivityNetServiceTest.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ActivityNetworkSettings.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ActivityNetworkState.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ActivityPermissions.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ActivityPermissionsRelay.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ActivityPersonalRecorder.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ActivityPhoneShake.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ActivityReplyFileOffer.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ActivityScanPeopleSearch.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ActivityScanProfiles.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ActivityScanStoryBoards.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ActivityScanWebCams.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ActivitySelectFileToSend.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ActivitySessionFileOffer.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ActivitySessionOptions.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ActivityShowHelp.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ActivitySnapShot.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ActivitySoundOptions.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ActivityStoryBoard.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ActivityTimedMessage.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ActivityToFriendBase.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ActivityToFriendChangeFriendship.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ActivityToFriendMultiSession.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ActivityToFriendRequestRelay.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ActivityToFriendTodGame.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ActivityToFriendVideoPhone.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ActivityToFriendViewSharedFiles.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ActivityToFriendVoicePhone.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ActivityUploads.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ActivityVideoOptions.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ActivityViewAudioFile.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ActivityViewLibraryFiles.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ActivityViewMySharedFiles.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ActivityViewVideoFile.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ActivityWebCamClient.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ActivityYesNoMsgBox.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/AssetBaseWidget.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/AssetFaceWidget.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/AssetPhotoWidget.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/AssetTextWidget.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/AssetVideoWidget.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/AssetVoiceWidget.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/AudioBuffer.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/AudioDeviceCoreWin.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/AudioDeviceWaveWin.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/AudioMixerMgrWin.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/AudioOutIo.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/AudioOutQt.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/AudioTestGenerator.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/MyQtSoundInput.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/MyQtSoundOutput.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/MySndMgr.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/VxWaveIn.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/VxWaveOut.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/AcceptCancelWidget.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/AvatarBar.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/BottomBarWidget.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ImagePickBar.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/PlayerGlWidget.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/RenderGlBaseWidget.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/RenderGlMatrix.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/RenderGlOffScreenSurface.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/RenderGlWidget.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/RenderGlWidgetFonts.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/RenderGlWidgetRender.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/RenderGlWidgetShaders.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/RenderGlWidgetTextures.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ShaderQt.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/VxAspectFrame.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/VxComboBox.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/VxContextMenu.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/ListEntryWidget.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/VxAvatarImage.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/VxFrame.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/VxMenuButton.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/VxMenuButtonBottom.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/VxMenuButtonTop.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/VxPushButton.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/VxComboBoxFileFilter.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/VxFlatButton.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/VxGuidQt.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/VxLabel.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/VxMyFileInfo.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/VxSndInstance.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/VxResourceToRealFile.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/VxScrollArea.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/VxShredderButton.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/VxSpinProgress.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/VxTagLabel.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/VxTilePositioner.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/VidWidget.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/VxWidgetBase.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/TodGameDefs.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/TodGameLogic.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/TodGameWidget.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/AppletBase.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/AppletKodi.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/AppletMgr.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/AppletPlayerBase.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/AppletRemoteControl.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/AppletSettings.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/AppletSharedContent.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/AppletTheme.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/AppletPlayerVideo.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/AppletUserIdentity.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/AppletLaunchWidget.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/AppletLaunchPage.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/AppCommon.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/AppCommonAudio.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/AppCommonEvents.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/AppCommonLogin.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/AppCommonRender.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/AppDefs.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/AppGlobals.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/AppProfile.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/AppSettings.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/Constants.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/EventsQtToGoTv.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/KodiThread.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/VxAppStyle.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/VxAppTheme.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/HomeWindow.cpp \
    $$PWD/GoTvApps/GoTvCommon/QtSource/VxAppDisplay.cpp \
    $$PWD/GoTvApps/GoTvPtoP/AppSource/GoTvPlayerSettings.cpp \
    $$PWD/GoTvApps/GoTvPtoP/AppSource/main.cpp \
    $$PWD/GoTvInterface/GoTvRenderFrame.cpp \
    $$PWD/GoTvInterface/IGoTv.cpp \
    $$PWD/GoTvInterface/IGoTvFromGui.cpp \
    $$PWD/GoTvInterface/IGoTvRender.cpp \
    $$PWD/GoTvInterface/IGoTvToGui.cpp \
    $$PWD/GoTvInterface/ILog.cpp \
    $$PWD/GoTvInterface/IToGui.cpp \
    $$PWD/GoTvInterface/OsInterface/OsInterface.cpp \
    $$PWD/GoTvInterface/OsWin32/IWin32.cpp \
    $$PWD/GoTvInterface/OsLinux/ILinux.cpp \
    $$PWD/GoTvInterface/OsAndroid/IAndroid.cpp \
    $$PWD/GoTvApps/GoTvPtoP/AppSource/exportdialog.cpp

