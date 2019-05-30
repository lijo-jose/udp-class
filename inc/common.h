#ifndef __COMMON_H__
#define __COMMON_H__

/*
#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
*/

inline uint64_t getTime()
{
    timeval curTime;
    gettimeofday(&curTime, NULL);
    uint64_t milli = curTime.tv_sec*1000 + curTime.tv_usec / 1000;    
}

#endif