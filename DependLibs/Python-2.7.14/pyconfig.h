#ifndef Py_PYCONFIG_H
#define Py_PYCONFIG_H

#if defined(TARGET_OS_ANDROID)
# include "pyconfig_android.h"
#elif defined(TARGET_OS_WINDOWS) || defined(_WIN64) || defined(WIN64) || defined(WIN32)
# include "pyconfig_windows.h"
#elif defined(TARGET_OS_LINUX)
# include "pyconfig_linux.h"
#else
echo target os not defined
#endif // defined(TARGET_OS_ANDROID)
#endif // Py_PYCONFIG_H