#pragma once

#if defined(TARGET_OS_ANDROID)
# include "pyconfig_android.h"
# ifndef PYTHONPATH
#	define PYTHONPATH ".\\DLLs;.\\lib;.\\lib\\plat-win;.\\lib\\lib-tk"
# endif
#elif defined(TARGET_OS_WINDOWS)
# include "pyconfig_windows.h"
# ifndef PYTHONPATH
#	define PYTHONPATH ".\\DLLs;.\\lib;.\\lib\\plat-win;.\\lib\\lib-tk"
# endif
#elif defined(TARGET_OS_LINUX)
# include "pyconfig_linux.h"
# ifndef PYTHONPATH
#	define PYTHONPATH ".\\DLLs;.\\lib;.\\lib\\plat-win;.\\lib\\lib-tk"
# endif
#else
echo target os not defined
#endif // defined(TARGET_OS_ANDROID)
