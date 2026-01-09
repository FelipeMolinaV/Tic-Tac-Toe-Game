#ifndef AUDIOSOURCE_H
#define AUDIOSOURCE_H

#include <SDL3/SDL.h>
#include <memory>

#include "Audio.h"
#include "GameObject.h"

class AudioSource : GameObject {

public:

    AudioSource(std::shared_ptr<Audio> audio);
    AudioSource(std::shared_ptr<Audio> audio, int volume);
    AudioSource(std::shared_ptr<Audio> audio, int volume, bool loopState);
    AudioSource(std::shared_ptr<Audio> audio, int volume, bool loopState, int fadeIn);
    AudioSource(std::shared_ptr<Audio> audio, int volume, bool loopState, int fadeIn, SDL_Point size, SDL_Point position);

    void Play();

    void SetVolume(int volume);
    void SetLoopState(bool loopState);
    void SetFadeIn(int fadeIn);

private:

    std::shared_ptr<Audio> mAudio;
    int mVolume;
    bool mLoopState;
    int mFadeIn;
};

#endif
