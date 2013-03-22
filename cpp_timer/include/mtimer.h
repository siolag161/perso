#ifndef _MTIMER_H_
#define _MTIMER_H_

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


class ExTimer
{
protected:
#ifdef _WIN64
   //define something for Windows (64-bit)
#elif _WIN32
   //define something for Windows (32-bit)

#elif __linux
    // linux
struct timespec start;
struct timespec end;

#endif //endif attributes

public:
ExTimer();

    void reset();
    long getTicks();
    double getElapsedTime();    

};



#endif
