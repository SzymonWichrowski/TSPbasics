#pragma once
#include <profileapi.h>

class Time {

    private:
    long long int frequency;
    long long int started;
    long long int elapsed;
    // Returns current clock counter value
    long long int read_QPC();

    public:
    Time();
    void timeStart();
    void timeStop();
    long long int getElapsed();
    long long int getFrequency();

};