#include "Font.h"

#include <stdexcept>

Font::Font(SDL_Renderer* renderer, const std::string& path, int pxSize){

    if (renderer == nullptr){
	throw std::runtime_error("Null pointer passed to renderer");
    }

    mRenderer = renderer;
    mTTF = TTF_OpenFont(path.c_str(), pxSize);

    if (mTTF == nullptr){
	throw std::runtime_error("Failed to open font");
    }
};

Font::~Font(){
    TTF_CloseFont(mTTF);
}


void Font::RenderText(SDL_Texture*& texture, SDL_Point& size, SDL_Point& position, std::string& text, size_t length, SDL_Color foregroundColor, int alpha){

    if (texture == nullptr){

	SDL_Surface* surface = TTF_RenderText_Solid(mTTF, text.c_str(), length, foregroundColor);	

	if (surface == nullptr){
	    throw std::runtime_error("Failed to create text surface");
	}

	texture = SDL_CreateTextureFromSurface(mRenderer, surface);

	SDL_DestroySurface(surface);
    }

    SDL_FRect dstRect = { (float) position.x, (float) position.y, (float) size.x, (float) size.y};
    SDL_SetTextureAlphaMod(texture, static_cast<Uint8>(alpha));
    SDL_RenderTexture(mRenderer, texture, nullptr, &dstRect);
}

void Font::GetAssetInfo(){
    // TODO: Implement
}
