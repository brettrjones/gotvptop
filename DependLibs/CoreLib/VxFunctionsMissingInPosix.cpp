#include "config_corelib.h"

#if 0 // moved to VxTime.cpp
#ifndef TARGET_OS_WINDOWS
#include <time.h>

uint64_t GetTickCount64()
{
// if the posix os has CLOCK_MONOTONIC defined then is better to use clock_gettime
// clock_gettime will not jump if user changes the current time. going backwards in time could cause issues
#ifdef CLOCK_MONOTONIC
    struct timespec now;
    clock_gettime( CLOCK_MONOTONIC, &now );
    return (( int64_t )now.tv_sec * 1000L ) + ( now.tv_nsec / 1000 );
#else
    struct timeval tv;
    if( gettimeofday( &tv, NULL ) != 0 )
        return 0;

    return ( ( int64_t )tv.tv_sec * 1000 ) + ( tv.tv_usec / 1000 );
#endif // CLOCK_MONOTONIC
}

#endif // TARGET_OS_WINDOWS
#endif //0 