#include "IGoTvDefs.h"
#include "IDefs.h"

//============================================================================
const char * describeAppModule( EAppModule appModule )
{
    switch( appModule )
    {
    case eAppModuleInvalid:
        return "eAppModuleInvalid";
    case eAppModuleAll:
        return "eAppModuleAll";
    case eAppModuleKodi:
        return "eAppModuleKodi";
    case eAppModulePtoP:
        return "eAppModulePtoP";
    case eAppModuleTest:
        return "eAppModuleTest";
    default:
        return "UNKNOWN EAppModule";
    }
}

//============================================================================
const char * describeModuleState( EModuleState moduleState )
{
    switch( moduleState )
    {
    case eModuleStateUnknown:
        return "eModuleStateUnknown";
    case eModuleStateInitialized:
        return "eModuleStateInitialized";
    case eModuleStateDeinitialized:
        return "eModuleStateDeinitialized";
    case eModuleStateInitError:
        return "eModuleStateInitError";
    default:
        return "UNKNOWN EModuleState";
    }
}

//============================================================================
// for use in database mainly
const char * getPluginName( EPluginType pluginType )
{
    switch( pluginType )
    {
    case ePluginTypeInvalid: return "ePluginTypeInvalid";
    case ePluginTypeAdmin: return "ePluginTypeAdmin";
    case ePluginTypeAboutMePage: return "ePluginTypeAboutMePage";
    case ePluginTypeAvatarImage: return "ePluginTypeAvatarImage";
    case ePluginTypeCamServer: return "ePluginTypeCamServer";
    case ePluginTypeChatRoom: return "ePluginTypeChatRoom";
    case ePluginTypeServiceConnectTest: return "ePluginTypeServiceConnectTest";
    case ePluginTypeClientConnectTest: return "ePluginTypeClientConnectTest";
    case ePluginTypeFileServer: return "ePluginTypeFileServer";
    case ePluginTypeFileXfer: return "ePluginTypeFileXfer";
    case ePluginTypeHostGroup: return "ePluginTypeHostGroup";
    case ePluginTypeHostGroupListing: return "ePluginTypeHostGroupListing";
    case ePluginTypeHostNetwork: return "ePluginTypeHostNetwork";
    case ePluginTypeMessenger: return "ePluginTypeMessenger";
    case ePluginTypeRandomConnect: return "ePluginTypeRandomConnect";
    case ePluginTypeRandomConnectRelay: return "ePluginTypeRandomConnectRelay";
    case ePluginTypeRelay: return "ePluginTypeRelay";
    case ePluginTypeStoryboard: return "ePluginTypeStoryboard";
    case ePluginTypeTruthOrDare: return "ePluginTypeTruthOrDare";
    case ePluginTypeVideoPhone: return "ePluginTypeVideoPhone";
    case ePluginTypeVoicePhone: return "ePluginTypeVoicePhone";
    case eMaxUserPluginType: return "eMaxUserPluginType";
    case eAppPluginsBegin: return "eAppPluginsBegin";
    case ePluginTypeCameraService: return "ePluginTypeCameraService";
    case ePluginTypeMJPEGReader: return "ePluginTypeMJPEGReader";
    case ePluginTypeMJPEGWriter: return "ePluginTypeMJPEGWriter";
    case ePluginTypePersonalRecorder: return "ePluginTypePersonalRecorder";
    case ePluginTypeNetServices: return "ePluginTypeNetServices";
    case ePluginTypeSearch: return "ePluginTypeSearch";
    case ePluginTypeSndReader: return "ePluginTypeSndReader";
    case ePluginTypeSndWriter: return "ePluginTypeSndWriter";
    case ePluginTypeWebServer: return "ePluginTypeWebServer";

    default:
        return "UnknownPlugin";
    }
}
