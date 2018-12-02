@rem Fetches (and builds if necessary) external dependencies

@rem Assume we start inside the Python source directory
call "Tools\buildbot\external-common.bat"
@rem BRJ removed 2008 now 2015 call "%VS90COMNTOOLS%\vsvars32.bat"
echo VS140COMNTOOLS is %VS140COMNTOOLS%
call "%VS140COMNTOOLS%\vsvars32.bat"

if not exist tcltk\bin\tcl85D.dll (
    @rem all and install need to be separate invocations, otherwise nmakehlp is not found on install
    cd tcl-8.5.2.1\win
    nmake -f makefile.vc DEBUG=1 INSTALLDIR=..\..\tcltk clean all
    nmake -f makefile.vc DEBUG=1 INSTALLDIR=..\..\tcltk install
    cd ..\..
)

if not exist tcltk\bin\tcl85.dll (
    @rem all and install need to be separate invocations, otherwise nmakehlp is not found on install
    cd tcl-8.5.2.1\win
    nmake -f makefile.vc DEBUG= INSTALLDIR=..\..\tcltk clean all
    nmake -f makefile.vc DEBUG= INSTALLDIR=..\..\tcltk install
    cd ..\..
)

if not exist tcltk\bin\tk85D.dll (
    cd tk-8.5.2.0\win
    nmake -f makefile.vc DEBUG=1 INSTALLDIR=..\..\tcltk TCLDIR=..\..\tcl-8.5.2.1 clean
    nmake -f makefile.vc DEBUG=1 INSTALLDIR=..\..\tcltk TCLDIR=..\..\tcl-8.5.2.1 all
    nmake -f makefile.vc DEBUG=1 INSTALLDIR=..\..\tcltk TCLDIR=..\..\tcl-8.5.2.1 install
    cd ..\..
)

if not exist tcltk\bin\tk85.dll (
    cd tk-8.5.2.0\win
    nmake -f makefile.vc DEBUG= INSTALLDIR=..\..\tcltk TCLDIR=..\..\tcl-8.5.2.1 clean
    nmake -f makefile.vc DEBUG= INSTALLDIR=..\..\tcltk TCLDIR=..\..\tcl-8.5.2.1 all
    nmake -f makefile.vc DEBUG= INSTALLDIR=..\..\tcltk TCLDIR=..\..\tcl-8.5.2.1 install
    cd ..\..
)

if not exist tcltk\lib\tix8.4.3\tix84D.dll (
    cd tix-8.4.3.5\win
    nmake -f makefile.vc DEBUG=1 MACHINE=IX86 TCL_DIR=..\..\tcl-8.5.2.1 TK_DIR=..\..\tk-8.5.2.0 INSTALL_DIR=..\..\tcltk clean
    nmake -f makefile.vc DEBUG=1 MACHINE=IX86 TCL_DIR=..\..\tcl-8.5.2.1 TK_DIR=..\..\tk-8.5.2.0 INSTALL_DIR=..\..\tcltk all
    nmake -f makefile.vc DEBUG=1 MACHINE=IX86 TCL_DIR=..\..\tcl-8.5.2.1 TK_DIR=..\..\tk-8.5.2.0 INSTALL_DIR=..\..\tcltk install
    cd ..\..
)

if not exist tcltk\lib\tix8.4.3\tix84.dll (
    cd tix-8.4.3.5\win
    nmake -f makefile.vc DEBUG= MACHINE=IX86 TCL_DIR=..\..\tcl-8.5.2.1 TK_DIR=..\..\tk-8.5.2.0 INSTALL_DIR=..\..\tcltk clean
    nmake -f makefile.vc DEBUG= MACHINE=IX86 TCL_DIR=..\..\tcl-8.5.2.1 TK_DIR=..\..\tk-8.5.2.0 INSTALL_DIR=..\..\tcltk all
    nmake -f makefile.vc DEBUG= MACHINE=IX86 TCL_DIR=..\..\tcl-8.5.2.1 TK_DIR=..\..\tk-8.5.2.0 INSTALL_DIR=..\..\tcltk install
    cd ..\..
)
