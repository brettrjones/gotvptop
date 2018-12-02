#include "rar.hpp"

#ifdef TARGET_OS_WINDOWS
int WinNT()
{
  static int dwPlatformId=-1,dwMajorVersion;
  if (dwPlatformId==-1)
  {
    OSVERSIONINFO WinVer;
    WinVer.dwOSVersionInfoSize=sizeof(WinVer);
    GetVersionEx(&WinVer);
    dwPlatformId=WinVer.dwPlatformId;
    dwMajorVersion=WinVer.dwMajorVersion;
  }
  return(dwPlatformId==VER_PLATFORM_WIN32_NT ? dwMajorVersion:0);
}
#endif
