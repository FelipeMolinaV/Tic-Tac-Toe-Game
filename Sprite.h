#ifndef SPRITE_H
#define SPRITE_H

#include <SDL3/SDL.h>
#include <memory>

#include "Texture.h"
#include "Asset.h"

class AssetFactory;

class Sprite : public Asset {

public:

    Sprite(SDL_Renderer* renderer, std::string path);
    Sprite(SDL_Renderer* renderer, std::string path, SDL_Point size);
    Sprite(SDL_Renderer* renderer, std::string path, SDL_Point size, SDL_Point position);

    SDL_Point& GetSize();
    void SetSize(int w, int h);
    SDL_Point& GetPosition();
    void SetPosition(int x, int y);
    void RenderSprite();
    void GetAssetInfo() override;


private:

    std::unique_ptr<Texture> mTexture; 
    
    // TODO: Replace SDL_Point to a proper class wrapper
    SDL_Point mSize;
    SDL_Point mPosition;

    friend class AssetFactory;

};

#endif
