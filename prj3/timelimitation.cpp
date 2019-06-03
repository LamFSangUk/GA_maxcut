#include "timelimitation.h"

clock_t start_tick(){
    clock_t t;
    t = clock();

    return t;
}

long get_consumed_msec(clock_t prev){
    clock_t t = clock();
    long msec = (t - prev) / (CLOCKS_PER_SEC / 1000);

    return msec;
}
