#ifndef __TIME_LIMIT_H__
#define __TIME_LIMIT_H__

#include <time.h>

#define TIME_LIMIT 500000           //500s

clock_t start_tick();
long get_consumed_msec(clock_t prev);

#endif
