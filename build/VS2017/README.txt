Solution Description

=== must build python first because other solutions depend on it
GoTvPython.sln - Python only 
Build Both Release and Debug x64 builds if plan to debug else just the release build

GoTvAll.sln - Contains all projects to build and run GoTvPtoP
NOTE: libkazza has a build issue. If you get error about linking asm object file 
	then rebuild it from the right click project menu
	
GoTvPtoPAndCore.sln - a cut down subset of GoTvAll.sln to most likely to change projects 
	This solution can be used after GoTvAll.sln is built to cut down on rebuild time



