/*****************************************************************
|
|      Neptune - Console Support: StdC Implementation
|
|      (c) 2002-2006 Gilles Boccon-Gibod
|      Author: Gilles Boccon-Gibod (bok@bok.net)
|
 ****************************************************************/

/*----------------------------------------------------------------------
|       includes
+---------------------------------------------------------------------*/
#include <libUPnP/config_libupnp.h>
#ifndef TARGET_OS_WINDOWS
#include <stdio.h>

#include "NptConfig.h"
#include "NptConsole.h"

/*----------------------------------------------------------------------
|       NPT_Console::Output
+---------------------------------------------------------------------*/
void
NPT_Console::Output(const char* message)
{
    printf("%s", message);
}

#endif // TARGET_OS_WINDOWS
