#ifndef SPRITE_H
#define SPRITE_H

#include <SDL3/SDL.h>
#include <memory>

#include "Texture.h"
#include "GameObject.h"

class AssetFactory;

class Sprite : public GameObject {

public:

    Sprite(int gameObjectID, std::shared_ptr<Texture> texture);
    Sprite(int gameObjectID, std::shared_ptr<Texture> texture, SDL_Point size);
    Sprite(int gameObjectID, std::shared_ptr<Texture> texture, SDL_Point size, SDL_Point position);

    void Render();
    SDL_Point GetTextureSize();
    void SetTextureSize(int x, int y);

private:

    std::shared_ptr<Texture> mTexture; 
    SDL_Point mTextureSize;

};

#endif
