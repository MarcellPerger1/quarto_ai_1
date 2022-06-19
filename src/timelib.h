#ifndef _TIMELIB_H_
#define _TIMELIB_H_

#include <time.h>
typedef struct timespec perf_t;
perf_t perf_counter();

perf_t tdiff(perf_t a, perf_t b);
int perft_toStr(perf_t t, char *dest, size_t dest_sz);
#endif
