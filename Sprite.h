#ifndef SPRITE_H
#define SPRITE_H

#include <SDL3/SDL.h>
#include "Texture.h"
#include <memory>

class Sprite{

public:

    SDL_Point& GetSize();
    void SetSize(int w, int h);
    SDL_Point& GetPosition();
    void SetPosition(int x, int y);
    void RenderSprite();

    // TODO: Move to private 
    Sprite(SDL_Renderer* renderer, std::string path);
    Sprite(SDL_Renderer* renderer, std::string path, SDL_Point size);
    Sprite(SDL_Renderer* renderer, std::string path, SDL_Point size, SDL_Point position);

private:

    // Private constructor and Destructor used by a friend factory class
    std::unique_ptr<Texture> mTexture; 
    
    // TODO: Replace SDL_Point to a proper class wrapper
    SDL_Point mSize;
    SDL_Point mPosition;
};

#endif
