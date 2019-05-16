#ifndef __TIME_LIMIT_H__
#define __TIME_LIMIT_H__

#include <time.h>

#define TIME_LIMIT 175000           //175s

clock_t start_tick();
long get_consumed_msec(clock_t prev);

#endif
