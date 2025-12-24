#include "Sprite.h"
#include <iostream>

Sprite::Sprite(std::shared_ptr<Texture> texture){
    mTexture = texture; 
}

Sprite::Sprite(std::shared_ptr<Texture> texture, SDL_Point size) : mSize(size) {
    mTexture = texture;
}

Sprite::Sprite(std::shared_ptr<Texture> texture, SDL_Point size, SDL_Point position) : mSize(size), mPosition(position) {
    mTexture = texture;
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

bool Sprite::IsColliding(int x, int y){

    // TODO: mPosition.x + mSize.x define the bounding
    if (!(x >= mPosition.x && x <= ( mPosition.x + mSize.x))){
	return false;
    }

    if (!(y >= mPosition.y && y <= ( mPosition.y + mSize.y))){
	return false;
    }

    return true;
}

void Sprite::Render(){
    mTexture->RenderTexture(mSize, mPosition);
}
