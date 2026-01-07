#ifndef FONTATLAS_H
#define FONTATLAS_H

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_h>

class FontAtlas : public Asset {

public:

    FontAtlas(SDL_Renderer* renderer, std::string& path, int pixelSize);
    ~FontAtlas();

private:

    TTF_Font* mFont;
    SDL_Renderer* mRenderer;
    std::vector<>
*};

#endif 
