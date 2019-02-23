
After the tools and enviroment to build has been setup

paths can get to long if building in a subfolder with a long paths
Check the source code out into short path folder like F:/gotvptop

As a test of your build enviroment
	1.) Open $(SRC_ROOT)/QtSimpleAppTest/QtSimpleTestProject.pro
	2.) Build and run to confirm a working build enviroment



NOTE: Visual Studio is no longer supported but the compiler install is required if building a windows version of GoTvPtoP
If building with Visual Studio then
	1.) Open $(SRC_ROOT)/build/VS2015/GoTvAll.sln
	2.) Rebuild All
	
If building with Qt
	1.) Open GoTvAll.pro with Qt creator
	2.) Click Projects and configure your kit(s)
	3.) You can uncheck Build Steps->Enable QML debugging and profiling.. there is no qml files used in project
	4.) In Build Enviroment make sure ANDROID_NDK_PLATFORM is set to android-21 .. NOT android-16 or you will get link errors
    5.) Could not get Qt to exclude the windows only subdirs
        so if building for windows you will have to uncomment them at the bottom of
        GoTvPythonLib.pro
    6.) build GoTvAll
    NOTE: python tcl and bsddb does not currently build and so is commented out

		
It will take a long time so be patient

on windows if you get error "make (e=87): The parameter is incorrect"
then the command line limit of 32k is exceeded
you may need to shorten your obj path
