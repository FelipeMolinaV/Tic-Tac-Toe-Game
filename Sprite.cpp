#include "Sprite.h"
#include <iostream>

Sprite::Sprite(int gameObjectID, std::shared_ptr<Texture> texture) 
    : 
    GameObject(gameObjectID) 
{
    mTexture = texture; 
    mVisibleState = true;
    SetCollisionState(true);
}

Sprite::Sprite(int gameObjectID, std::shared_ptr<Texture> texture, SDL_Point size) 
    : 
    GameObject(gameObjectID, size) 
{
    mTexture = texture;
    mTextureSize = size; 
    mVisibleState = true;
    SetCollisionState(true);
}

Sprite::Sprite(int gameObjectID, std::shared_ptr<Texture> texture, SDL_Point size, SDL_Point position) 
    : 
    GameObject(gameObjectID, size, position) 
{
    mTexture = texture;
    mTextureSize = size;
    mVisibleState = true;
    SetCollisionState(true);
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

void Sprite::SetVisibleState(bool state){
    mVisibleState = state;
}

bool Sprite::GetVisibleState(){
    return mVisibleState;
}

void Sprite::Render(){
    if (mVisibleState){
	if ((mTextureSize.x == 0 && mTextureSize.y == 0) || (mSize.x == mTextureSize.x && mSize.y == mTextureSize.y )){
	    mTexture->RenderTexture(mSize, mPosition);
	}
	else {
	    mTexture->RenderTexture(mTextureSize, mPosition);
	}
    }
}

void Sprite::Render(Uint8 alpha){
    if (mVisibleState){
	if ((mTextureSize.x == 0 && mTextureSize.y == 0) || (mSize.x == mTextureSize.x && mSize.y == mTextureSize.y )){
	    mTexture->RenderTexture(mSize, mPosition, alpha);
	}
	else {
	    mTexture->RenderTexture(mTextureSize, mPosition, alpha);
	}
    }
}
