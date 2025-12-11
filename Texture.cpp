#include "Texture.h"
#include <stdexcept>

Texture::Texture(SDL_Renderer* renderer, std::string path){    

    if (renderer == nullptr){
	throw std::runtime_error("Null pointer passed to renderer");
    }

    mRenderer = renderer;

    mTexture = IMG_LoadTexture(mRenderer, path.c_str());
    
    if (mTexture == nullptr){
	throw std::runtime_error(std::string("Failed to load texture from path: [") + path + "]");
    }
} 

Texture::~Texture(){
    SDL_DestroyTexture(mTexture);
}

void Texture::RenderTexture(SDL_Point& size, SDL_Point& position){
    SDL_FRect dstRect = { (float) position.x, (float) position.y, (float) size.x, (float) size.y};
    SDL_RenderTexture(mRenderer, mTexture, nullptr, &dstRect);
}
