#include "AudioSource.h"

#include <stdexcept>


AudioSource::AudioSource(std::shared_ptr<Audio> audio){
    mAudio = audio;
}

AudioSource::AudioSource(std::shared_ptr<Audio> audio, int volume){

    if (!(volume >= 0 && volume <= 100)){
	throw std::runtime_error("Volume must be greater than or equal to 0 and less than or equal to 100");
    }

    mAudio = audio;
    mVolume = volume;
}

AudioSource::AudioSource(std::shared_ptr<Audio> audio, int volume, bool loopState){

    if (!(volume >= 0 && volume <= 100)){
	throw std::runtime_error("Volume must be greater than or equal to 0 and less than or equal to 100");
    }

    mAudio = audio;
    mVolume = volume;
    mLoopState = loopState;
}

AudioSource::AudioSource(std::shared_ptr<Audio> audio, int volume, bool loopState, int fadeIn){

    if (!(volume >= 0 && volume <= 100)){
	throw std::runtime_error("Volume must be greater than or equal to 0 and less than or equal to 100");
    }

    mAudio = audio;
    mVolume = volume;
    mLoopState = loopState;
    mFadeIn = fadeIn;
}

AudioSource::AudioSource(std::shared_ptr<Audio> audio, 
			 int volume, 
			 bool loopState, 
			 int fadeIn, 
			 SDL_Point size, 
			 SDL_Point position)
    : GameObject(size, position) 
{

    if (!(volume >= 0 && volume <= 100)){
	throw std::runtime_error("Volume must be greater than or equal to 0 and less than or equal to 100");
    }

    mAudio = audio;
    mVolume = volume;
    mLoopState = loopState;
    mFadeIn = fadeIn;
}

void AudioSource::Play(){
    mAudio->PlayAudio(mVolume,
		      (mLoopState) ? -1 : 1,
		      mFadeIn);
}

void AudioSource::SetVolume(int volume){

    if (!(volume >= 0 && volume <= 100)){
	throw std::runtime_error("Volume must be greater than or equal to 0 and less than or equal to 100");
    }

    mVolume = volume;
}
void AudioSource::SetLoopState(bool loopState){
    mLoopState = loopState;
}
void AudioSource::SetFadeIn(int fadeIn){
    mFadeIn = fadeIn;
}
