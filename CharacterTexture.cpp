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
}

void CharacterTexture::RenderCharacterTexture(SDL_Point& size, SDL_Point& position, int alpha){
    SDL_FRect dstRect = { (float) position.x, (float) position.y, (float) size.x, (float) size.y};
    SDL_SetTextureAlphaMod(mTexture, static_cast<Uint8>(alpha));
    SDL_RenderTexture(mRenderer, mTexture, nullptr, &dstRect);
}
