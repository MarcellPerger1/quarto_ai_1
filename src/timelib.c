#include <stdio.h>
#include <time.h>

#include "timelib.h"

#if defined(CLOCK_HIGHRES)
#  define PERF_CLOCK CLOCK_HIGHRES
#elif defined(CLOCK_MONOTONIC)
#  define PERF_CLOCK CLOCK_MONOTONIC
#else 
#  warning using realtime clock; results may be slightly inaccurate
#  define PERF_CLOCK CLOCK_REALTIME
#endif


perf_t perf_counter(){
  perf_t temp_tspec;
  clock_gettime(PERF_CLOCK, &temp_tspec);
  return temp_tspec;
}

#define _abs_diff(a, b) ((a) >= (b) ? (a) - (b) : (b) - (a))
#define NSEC_IN_SEC 1000000000

// calculate abs(`a` - `b`)
perf_t tdiff(perf_t a, perf_t b){
  // TODO assert that a and b are not too big to cause overflow
  long nsec;
  time_t sec;
  if(a.tv_sec == b.tv_sec){
    nsec = _abs_diff(a.tv_nsec, b.tv_nsec);
    sec = 0;
  } else if(a.tv_sec > b.tv_sec){
    sec = a.tv_sec - b.tv_sec;
    nsec = a.tv_nsec - b.tv_nsec;
  } else {
    sec = b.tv_sec - a.tv_sec;
    nsec = b.tv_nsec - a.tv_nsec;
  }
  if(nsec < 0){
    nsec += NSEC_IN_SEC;
    sec -= 1;
  }
  perf_t res = {.tv_sec=sec, .tv_nsec=nsec};
  return res;
}


int perft_toStr(perf_t t, char *dest, size_t dest_sz){
  return snprintf(dest, dest_sz, "%lld.%09ld", (long long) t.tv_sec, t.tv_nsec);
}
