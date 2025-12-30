#ifndef TIMER_H
#define TIMER_H

#include <SDL3/SDL.h>
#include <iostream>
#include <functional>

class Timer{

public:

    Timer();
    void StartTimer(int duration, std::function<void()> function);

private:

    int mDuration;
    int mCurrentTime;
    int mCount;
    int mLastTime; 
    bool mRunning;
};

#endif
