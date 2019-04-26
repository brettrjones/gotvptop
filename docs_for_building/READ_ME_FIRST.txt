
If you are unfamilar with GoTvPtoP you might want to read GoTvPtoP_Terminology.txt

After the tools and enviroment to build in your enviroment has been setup.

paths can get to long if building in a subfolder with a long paths
Check the source code out into short path folder like F:/gotvptop

As a test of your build enviroment
  If building with Visual Studio
	1.) Open $(SRC_ROOT)/SandboxApps/QtOpenglThreadTestApp/build/VS2017/QtOpenglThreadTest.sln
	2.) Build and run to confirm a working build enviroment
  If building with Qt
	1.) Open $(SRC_ROOT)/SandboxApps/QtOpenglThreadTestApp/QtOpenglThreadTest.pro
	2.) Build and run to confirm a working build enviroment


NOTE: Only Visual Studio 2017 is supported and the compiler install is required if building a windows version of GoTvPtoP
If building with Visual Studio then
	1.) copy contents of $(SRC_ROOT)/deploy-common and $(SRC_ROOT)/deploy-windows to $(SRC_ROOT)/bin-Windows
	2.) Open $(SRC_ROOT)/build/VS2017/GoTvPython.sln
	3.) Rebuild All
	4.) Open $(SRC_ROOT)/build/VS2015/GoTvAll.sln
	5.) Rebuild All
	6.) optionally you can use GoTvPtoPAndCore.sln for build/Debug ( it contains a subset of GoTvAll.sln projects which are likely to be modified )
	
If building with Qt
	1.) copy contents of $(SRC_ROOT)/deploy-common and $(SRC_ROOT)/deploy-windows to $(SRC_ROOT)/bin-Windows
	2.) Open GoTvAll.pro with Qt creator
	3.) Click Projects and configure your kit(s)
	4.) You can uncheck Build Steps->Enable QML debugging and profiling.. there is no qml files used in project
	5.) In Build Enviroment make sure ANDROID_NDK_PLATFORM is set to android-21 .. NOT android-16 or you will get link errors
    6.) Could not get Qt to exclude the windows only subdirs
        so if building for windows you will have to uncomment them at the bottom of
        GoTvPythonLib.pro
    7.) build GoTvAll
    NOTE: python tcl and bsddb does not currently build and so is commented out

		
It will take a long time so be patient

on windows if you get error "make (e=87): The parameter is incorrect"
then the command line limit of 32k is exceeded
you may need to shorten your obj path

Some Words Of Advice
If you live in USA you should be paranoid about privacy.
In USA from the "WAR ON CRIME", "WAR ON DRUGS", "WAR OF TERROR" and now the "WAR ON MEXICANS"
we have the highest percentage of our citizens in jail of any country in the world.

In the USA you are your IP Address even if someone else used it. You can be sued for thousands of dollars using just your IP Address as your identity. 
GoTvPtoP and Kodi use 3rd Party plugins, be paranoid that they might cause copywrite infringement.
In the USA copywrite infringement penalties can be over a $30,000.00 fine per work infringed and up to 5 years in jail

Use a VPN if possible. NordVPN seems a good choice but it is the only one I have used.
Research how to improve your privacy.
 
