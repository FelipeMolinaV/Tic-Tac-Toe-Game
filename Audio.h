#ifndef AUDIO_H
#define AUDIO_H

#include <SDL3_mixer/SDL_mixer.h>
#include <string>

#include "Asset.h"

class Audio : public Asset {

public:

    Audio(MIX_Mixer* mixer, std::string path);
    ~Audio();

    void PlayAudio(int volume, int loops, int fadeIn);

    void GetAssetInfo() override;

private:

    MIX_Track* mTrack;
    MIX_Audio* mAudio;
    SDL_PropertiesID mProperties;
};

#endif 
