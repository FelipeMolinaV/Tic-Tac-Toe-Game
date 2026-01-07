#ifndef CHARACTERTEXTURE_H
#define CHARACTERTEXTURE_H

#include <SDL3/SDL.h>

// simple wrapper RAII to use in FontAtlas
class CharacterTexture{

public:

    CharacterTexture(SDL_Renderer* mRenderer, SDL_Surface* surface);
    ~CharacterTexture();

    void RenderCharacterTexture(SDL_Point& size, SDL_Point& position, int alpha);

private:

    SDL_Texture* mTexture;
    SDL_Renderer* mRenderer;
};

#endif
