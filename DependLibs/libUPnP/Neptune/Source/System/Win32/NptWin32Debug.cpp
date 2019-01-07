/*****************************************************************
|
|   Neptune - Debug Support: Win32 Implementation
|
|   (c) 2002-2006 Gilles Boccon-Gibod
|   Author: Gilles Boccon-Gibod (bok@bok.net)
|
 ****************************************************************/

/*----------------------------------------------------------------------
|   includes
+---------------------------------------------------------------------*/
#include <libUPnP/config_libupnp.h>
#ifdef TARGET_OS_WINDOWS
#include <stdio.h>
#if defined(_XBOX)
#include <xtl.h>
#else
#include <WinSock2.h>
#include <windows.h>
#endif

#include "NptConfig.h"
#include "NptDefs.h"
#include "NptTypes.h"
#include "NptDebug.h"
#include <memory>

/*----------------------------------------------------------------------
|   NPT_DebugOutput
+---------------------------------------------------------------------*/
void
NPT_DebugOutput(const char* message)
{
  int result = MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, message, -1, nullptr, 0);
  if (result == 0)
    return;

  auto newStr = std::make_unique<wchar_t[]>(result + 1);
  result = MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, message, result, newStr.get(), result);

  if (result == 0)
    return;

  OutputDebugStringW(newStr.get());
}

#endif // TARGET_OS_WINDOWS
