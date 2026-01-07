#ifndef FONT_H
#define FONT_H

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>

#include "Asset.h"

class Font : public Asset {

public:

    Font(SDL_Renderer* renderer, const std::string& path, int pxSize);
    ~Font();

    void RenderText(SDL_Texture*& texture, SDL_Point& size, SDL_Point& position, std::string& text, size_t length, SDL_Color foregroundColor, int alpha);   

    void GetAssetInfo() override;

private:

    TTF_Font* mTTF;
    SDL_Renderer* mRenderer;
};

#endif
