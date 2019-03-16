#pragma once


enum EModules
{
    eModuleUnknown = 0,
    eModuleAll,
    eModuleKodi,
    eModulePtoP,
    eModuleFfmpeg,

    eMaxModule // must be last
};

enum EModuleState
{
	eModuleStateUnknown = 0,
	eModuleStateInitialized,
	eModuleStateDeinitialized,

	eMaxModuleState // must be last
};



enum EAppModule
{
    eAppModuleInvalid = 0,
    eAppModuleAll,
    eAppModuleKodi,
    eAppModulePtoP,
    eAppModuleTest,

    eMaxAppModule // must be last
};
