#include "Sprite.h"

Sprite::Sprite(SDL_Renderer* renderer, std::string path){
    mTexture = new Texture(renderer, path);
}

Sprite::Sprite(SDL_Renderer* renderer, std::string path, SDL_Point size) : mSize(size) {
    mTexture = new Texture(renderer, path);
}

Sprite::Sprite(SDL_Renderer* renderer, std::string path, SDL_Point size, SDL_Point position) : mSize(size), mPosition(position) {
    mTexture = new Texture(renderer, path);
}

Sprite::~Sprite(){
    delete mTexture;
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
