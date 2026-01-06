#include "Sprite.h"
#include <iostream>

Sprite::Sprite(std::shared_ptr<Texture> texture) 
{
    mTexture = texture; 
    mVisibleState = true;
    SetCollisionState(true);
    mAlpha = 255;
}

Sprite::Sprite(std::shared_ptr<Texture> texture, SDL_Point size) 
    : 
    GameObject(size) 
{
    mTexture = texture;
    mTextureSize = size; 
    mVisibleState = true;
    SetCollisionState(true);
    mAlpha = 255;
}

Sprite::Sprite(std::shared_ptr<Texture> texture, SDL_Point size, SDL_Point position) 
    : 
    GameObject(size, position) 
{
    mTexture = texture;
    mTextureSize = size;
    mVisibleState = true;
    SetCollisionState(true);
    mAlpha = 255;
}

Sprite::Sprite(std::shared_ptr<Texture> texture, SDL_Point size, SDL_Point position, int layer) 
    : 
    GameObject(size, position) 
{
    mTexture = texture;
    mTextureSize = size;
    mVisibleState = true;
    SetCollisionState(true);
    mLayer = layer;
    mAlpha = 255;
}

Sprite::Sprite(std::shared_ptr<Texture> texture, SDL_Point size, SDL_Point position, int layer, int alpha) 
    : 
    GameObject(size, position) 
{
    mTexture = texture;
    mTextureSize = size;
    mVisibleState = true;
    SetCollisionState(true);
    mLayer = layer;
    mAlpha = alpha;
}

void Sprite::SetTexture(std::shared_ptr<Texture> texture){
    mTexture = texture;
    SetTextureSize(mTextureSize.x, mTextureSize.y);
}

SDL_Point Sprite::GetTextureSize(){
    return mTextureSize;
}

void Sprite::SetTextureSize(int x, int y){
    mTextureSize.x = x;
    mTextureSize.y = y;
}

void Sprite::SetLayer(int layer){
    mLayer = layer;
}

int Sprite::GetLayer(){
    return mLayer;
}

void Sprite::SetAlpha(int alpha){
    mAlpha = alpha;
}

int Sprite::GetAlpha(){
    return mAlpha;
}

void Sprite::SetVisibleState(bool state){
    mVisibleState = state;
}

bool Sprite::GetVisibleState(){
    return mVisibleState;
}

void Sprite::Render(){
    if (mVisibleState){
	if ((mTextureSize.x == 0 && mTextureSize.y == 0) || (mSize.x == mTextureSize.x && mSize.y == mTextureSize.y )){
	    mTexture->RenderTexture(mSize, mPosition, mAlpha);
	}
	else {
	    mTexture->RenderTexture(mTextureSize, mPosition, mAlpha);
	}
    }
}

