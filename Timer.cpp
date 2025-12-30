#include "Timer.h"

Timer::Timer(){
    mRunning = false;
}

void Timer::StartTimer(int duration, std::function<void()> function){
    
    if (!mRunning){
	mRunning = true;
	mCurrentTime = SDL_GetTicks();
	mDuration = mCurrentTime + duration;
    }
    else {

	mCurrentTime = SDL_GetTicks();

	if (mCurrentTime >= mDuration){
	    mRunning = false;
	    mCurrentTime = 0;
	    function();
	}
    }
}
