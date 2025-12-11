#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <string>

class Texture{

public:

    Texture(SDL_Renderer* renderer, std::string path);
    ~Texture();
    void RenderTexture(SDL_Point& size, SDL_Point& position);

private:

    SDL_Texture* mTexture;
    SDL_Renderer* mRenderer;
};

#endif
