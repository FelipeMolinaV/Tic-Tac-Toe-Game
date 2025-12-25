#include "Sprite.h"
#include <iostream>

Sprite::Sprite(int gameObjectID, std::shared_ptr<Texture> texture) 
    : 
    GameObject(gameObjectID) 
{
    mTexture = texture; 
}

Sprite::Sprite(int gameObjectID, std::shared_ptr<Texture> texture, SDL_Point size) 
    : 
    GameObject(gameObjectID, size) 
{
    mTexture = texture;
    mTextureSize = size; 
}

Sprite::Sprite(int gameObjectID, std::shared_ptr<Texture> texture, SDL_Point size, SDL_Point position) 
    : 
    GameObject(gameObjectID, size, position) 
{
    mTexture = texture;
    mTextureSize = size;
}

SDL_Point Sprite::GetTextureSize(){
    return mTextureSize;
}

void Sprite::SetTextureSize(int x, int y){
    mTextureSize.x = x;
    mTextureSize.y = y;
}

void Sprite::Render(){
    if ((mTextureSize.x == 0 && mTextureSize.y == 0) || (mSize.x == mTextureSize.x && mSize.y == mTextureSize.y )){
	mTexture->RenderTexture(mSize, mPosition);
    }
    else {
	mTexture->RenderTexture(mTextureSize, mPosition);
    }
}
