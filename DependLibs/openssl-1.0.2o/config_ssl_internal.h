#include <GoTvCompilerConfig.h>
/* OpenSSL was configured with the following options: */
#ifdef TARGET_OS_WINDOWS
# ifdef ARCH_32_BITS
#  define OPENSSL_SYSNAME_WIN32
# else
#  define OPENSSL_SYSNAME_WIN64
# endif // ARCH_32_BITS
#elif TARGET_OS_LINUX
#  define OPENSSL_SYS_UNIX
#endif // TARGET_OS_WINDOWS

#ifdef ARCH_32_BITS
# define THIRTY_TWO_BIT
# define THIRTY_TWO_BIT_LONG
#else
# define SIXTY_FOUR_BIT
# define SIXTY_FOUR_BIT_LONG
#endif 