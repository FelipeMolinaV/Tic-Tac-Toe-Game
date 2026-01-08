#ifndef FONTATLAS_H
#define FONTATLAS_H

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <unordered_map>
#include <memory>
#include <string>

#include "Asset.h"
#include "CharacterTexture.h"

class FontAtlas : public Asset {

public:

    FontAtlas(SDL_Renderer* renderer, std::string& path, int pixelSize, SDL_Color foregroundColor);
    ~FontAtlas();

    void RenderText(SDL_Point& size, SDL_Point& position, std::string& text, int alpha);

    void GetAssetInfo() override;

private:

    TTF_Font* mFont;
    SDL_Renderer* mRenderer;
    std::unordered_map<char, std::shared_ptr<CharacterTexture>> mCharacters;
};

#endif 
