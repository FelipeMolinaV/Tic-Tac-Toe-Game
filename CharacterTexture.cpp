#include "CharacterTexture.h"

#include <stdexcept>

CharacterTexture::CharacterTexture(SDL_Renderer* renderer, SDL_Surface* surface){

    if (renderer == nullptr){
	throw std::runtime_error("Null pointer passed to renderer");
    }

    mRenderer = renderer;

    if (surface == nullptr){
	throw std::runtime_error("Null pointer passed to surface");
    }

    mTexture = SDL_CreateTextureFromSurface(mRenderer, surface);
}

CharacterTexture::~CharacterTexture(){
    SDL_DestroyTexture(mTexture);
    mTexture = nullptr;
}

void CharacterTexture::RenderCharacterTexture(SDL_FRect destinationRect, int alpha){
    SDL_SetTextureAlphaMod(mTexture, static_cast<Uint8>(alpha));
    SDL_RenderTexture(mRenderer, mTexture, nullptr, &destinationRect);
}
