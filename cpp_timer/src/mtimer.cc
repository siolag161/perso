#include "mtimer.h"

#ifdef _WIN64
   //define something for Windows (64-bit)
#elif _WIN32
   //define something for Windows (32-bit)
    #include <windows.h>
#elif __APPLE__
    #include "TargetConditionals.h"
    #if TARGET_OS_IPHONE    
         // iOS device
    #elif TARGET_IPHONE_SIMULATOR
        // iOS Simulator
    #elif TARGET_OS_MAC
        // Other kinds of Mac OS
    #else
        // Unsupported platform
    #endif

#elif __linux
    // linux
    #include <time.h>
#elif __unix // all unices not caught above
    // Unix
#elif __posix
// POSIX
#endif

void ExTimer::reset()
{
    clock_gettime(CLOCK_MONOTONIC, &start);
    end = start;
    
}

long ExTimer::getTicks()
{
    return 0;
}

double ExTimer::getElapsedTime()
{
    clock_gettime(CLOCK_MONOTONIC, &end);
    long sec = end.tv_sec-start.tv_sec;
    long nsec = end.tv_nsec-start.tv_nsec;
    return (sec*1000000+nsec/1000);
}

ExTimer::ExTimer()
{
    reset();
}
