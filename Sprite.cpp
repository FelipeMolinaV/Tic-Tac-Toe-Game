#include "Sprite.h"
#include <iostream>

Sprite::Sprite(SDL_Renderer* renderer, std::string path){
    mTexture = std::make_unique<Texture>(renderer, path); 
}

Sprite::Sprite(SDL_Renderer* renderer, std::string path, SDL_Point size) : mSize(size) {
    mTexture = std::make_unique<Texture>(renderer, path);
}

Sprite::Sprite(SDL_Renderer* renderer, std::string path, SDL_Point size, SDL_Point position) : mSize(size), mPosition(position) {
    mTexture = std::make_unique<Texture>(renderer, path);
}


SDL_Point& Sprite::GetSize(){
    return mSize;
}

void Sprite::SetSize(int w, int h){
    mSize.x = w;
    mSize.y = h;
}

SDL_Point& Sprite::GetPosition(){
    return mPosition;
}

void Sprite::SetPosition(int x, int y){
    mPosition.x = x;
    mPosition.y = y;
}

void Sprite::RenderSprite(){
    mTexture->RenderTexture(mSize, mPosition);
}

void Sprite::GetAssetInfo(){
    std::cout << "----- Sprite info -----" << '\n';
}
