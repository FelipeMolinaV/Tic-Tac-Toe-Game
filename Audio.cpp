#include "Audio.h"

#include <SDL3/SDL.h>
#include <iostream>
#include <stdexcept>
#include <cassert>
#include <format>

Audio::Audio(MIX_Mixer* mixer, std::string path){

    if (mixer == nullptr){
	throw std::runtime_error("Null pointer passed to mixer");
    }

    mTrack = MIX_CreateTrack(mixer);

    if (mTrack == nullptr){
	throw std::runtime_error("Failed to create Track");
    }

    mAudio = MIX_LoadAudio(mixer, path.c_str(), true);

    if (mAudio == nullptr){
	throw std::runtime_error(std::format("Failed to load audio from path:[{}]", path));
    }

    if (!MIX_SetTrackAudio(mTrack, mAudio)){
	throw std::runtime_error("Failed to set track's audio");
    }
}

Audio::~Audio(){
    MIX_DestroyTrack(mTrack);
    MIX_DestroyAudio(mAudio);
    SDL_DestroyProperties(mProperties);
}

void Audio::PlayAudio(int volume, int loops, int fadeIn){

    assert(volume >= 0 && volume <= 100 && "Volume must be greater than or equal to 0 and less than or equal to 100"); 

    float newVolume = (float)(volume/100);

    if (MIX_GetTrackGain(mTrack) != newVolume){
	MIX_SetTrackGain(mTrack, newVolume);
    }

    SDL_SetNumberProperty(mProperties, MIX_PROP_PLAY_LOOPS_NUMBER, loops); 
    SDL_SetNumberProperty(mProperties, MIX_PROP_PLAY_FADE_IN_MILLISECONDS_NUMBER, fadeIn); 

    if (!MIX_PlayTrack(mTrack, mProperties)){
	std::cout << "Failed to play track" << std::endl;
    }

    SDL_ClearProperty(mProperties, MIX_PROP_PLAY_LOOPS_NUMBER); 
    SDL_ClearProperty(mProperties, MIX_PROP_PLAY_FADE_IN_MILLISECONDS_NUMBER); 
}

void Audio::GetAssetInfo(){
}
