#include "Time.h"
#include <profileapi.h>

Time::Time() {
    QueryPerformanceFrequency((LARGE_INTEGER *) &frequency);
}

long long int Time::read_QPC() {
    LARGE_INTEGER count;
    QueryPerformanceCounter(&count);
    return(count.QuadPart);
}

void Time::timeStart() {
    started = read_QPC();
}

void Time::timeStop() {
    elapsed = read_QPC() - started;
}

long long int Time::getElapsed() {
    return elapsed;
}

long long int Time::getFrequency() {
    return frequency;
}

