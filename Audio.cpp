#include "Audio.h"

#include <iostream>
#include <stdexcept>
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
}

void Audio::PlayAudio(){
    if (!MIX_PlayTrack(mTrack, 0)){
	std::cout << "Failed to play track" << std::endl;
    }
}

void Audio::GetAssetInfo(){
}
