#ifndef SPRITE_H
#define SPRITE_H

#include <SDL3/SDL.h>
#include <memory>

#include "Texture.h"

class AssetFactory;

class Sprite {

public:

    Sprite(std::shared_ptr<Texture> texture);
    Sprite(std::shared_ptr<Texture> texture, SDL_Point size);
    Sprite(std::shared_ptr<Texture> texture, SDL_Point size, SDL_Point position);

    SDL_Point& GetSize();
    void SetSize(int w, int h);
    SDL_Point& GetPosition();
    void SetPosition(int x, int y);

    // Check collision with position
    bool IsColliding(int x, int y);

    void Render();


private:

    std::shared_ptr<Texture> mTexture; 
    
    // TODO: Replace SDL_Point to a proper class wrapper
    SDL_Point mSize;
    SDL_Point mPosition;

};

#endif
