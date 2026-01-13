#include "Sprite.h"

#include <iostream>
#include <utility>

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

Sprite::Sprite(Sprite&& other)
: GameObject(std::move(other))
{
    *this = std::move(other);
}

Sprite& Sprite::operator=(Sprite&& other){
    if (this != &other){

	this->mSize = std::move(other.mSize);
	this->mPosition = std::move(other.mPosition);
	this->mTexture = std::move(other.mTexture);
	this->mVisibleState = std::move(other.mVisibleState);
	this->mLayer = std::move(other.mLayer);
	this->mAlpha = std::move(other.mAlpha);
    }
    return *this;
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
    if (GetActive()){
	if (mVisibleState){
	    if ((mTextureSize.x == 0 && mTextureSize.y == 0) || (mSize.x == mTextureSize.x && mSize.y == mTextureSize.y )){
		mTexture->RenderTexture(mSize, mPosition, mAlpha);
	    }
	    else {
		mTexture->RenderTexture(mTextureSize, mPosition, mAlpha);
	    }
	}
    }
}

