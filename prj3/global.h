#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <vector>
#include <cassert>

#include "graph.h"
#include "timelimitation.h"

#define INT_MAX 2147483647
#define INT_MIN -2147483648

// For genetic algoritm
#define NUM_SOLUTION            100
#define THRESHOLD_CONVERGENCE   0.001


// Mode
//#define EXPERIMENT
#define RELEASE

#ifdef EXPERIMENT
#define RESULT
//#define DETAIL
#endif

#ifdef RELEASE
#define NDEBUG
#endif

#endif
