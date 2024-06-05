#ifndef clock_h
#define clock_h
// exports: clock_seconds()
#include <windows.h>

#ifdef __cplusplus
extern "C" {
#endif

static inline double clock_seconds(void) { // since_boot
    LARGE_INTEGER qpc;
    QueryPerformanceCounter(&qpc);
    static double one_over_freq;
    if (one_over_freq == 0) {
        LARGE_INTEGER frequency;
        QueryPerformanceFrequency(&frequency);
        one_over_freq = 1.0 / (double)frequency.QuadPart;
    }
    return (double)qpc.QuadPart * one_over_freq;
}

#ifdef __cplusplus
} // extern "C"
#endif

#endif // clock_h
