Solution Description

Before running a solution you need to copy resouces to the bin directory
For windows copy the contents of deploy-common and deploy-windows to the bin-Windows directory 

GoTvAll.sln - Contains all projects to build and run GoTvPtoP
NOTE: libkazza has a build issue. If you get error about linking asm object file 
	then rebuild it from the right click project menu
	
GoTvPtoPAndCore.sln - a cut down subset of GoTvAll.sln to most likely to change projects 
	This solution can be used after GoTvAll.sln is built to cut down on rebuild time

GoTvPython.sln - Python only 

