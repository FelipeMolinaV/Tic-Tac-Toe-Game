#include "FontAtlas.h"

#include <format>

FontAtlas::FontAtlas(SDL_Renderer* renderer, std::string& path, int pixelSize, SDL_Color foregroundColor){

    mFont = TTF_OpenFont(path.c_str(), pixelSize);
    
    if (mFont == nullptr){
	throw std::runtime_error("Failet to load Font");
    }

    if (renderer == nullptr){
	throw std::runtime_error("Null pointer passed to renderer");
    }
    
    mRenderer = renderer;

    // Create CharacterTexture pointers for space, 0-9, a-z and A-Z
    mCharacters.reserve(63);
    
    auto createCharacterPointer = [&](int i){
	
	char character = static_cast<char>(i);

	if (!TTF_FontHasGlyph(mFont, character)){
	    throw std::runtime_error(std::format("Font has no '{}' character", character));
	}

	SDL_Surface* characterSurface = TTF_RenderText_Solid(mFont, std::string(1, character).c_str(), 0, foregroundColor);

	if (characterSurface == nullptr){
	    throw std::runtime_error("Failed to create surface from text");
	}

	mCharacters[character] = std::make_shared<CharacterTexture>(mRenderer, characterSurface);

	SDL_DestroySurface(characterSurface);
    };

    createCharacterPointer(static_cast<int>(' '));
    
    // 0-9
    for (int i = static_cast<int>('0'); i <= static_cast<int>('9'); i++){
	createCharacterPointer(i);
    }

    // a-z
    for (int i = static_cast<int>('a'); i <= static_cast<int>('z'); i++){
	createCharacterPointer(i);
    }

    // A-Z
    for (int i = static_cast<int>('A'); i <= static_cast<int>('Z'); i++){
	createCharacterPointer(i);
    }
}

void FontAtlas::RenderText(SDL_Point& size, SDL_Point& position, std::string& text, int alpha){

    SDL_FRect dstRect;

    for (size_t i = 0; i < text.length(); i++){

	float posX = (float)(position.x + ((size.x/text.length())*i));
	float sizeX = (float)(size.x/text.length());
	dstRect = {posX, (float) position.y, sizeX, (float) size.y};

	auto& characterTexture = mCharacters[text[i]];
	characterTexture->RenderCharacterTexture(dstRect, alpha);
    }
}

FontAtlas::~FontAtlas(){
    TTF_CloseFont(mFont);
    mCharacters.clear();
}

void FontAtlas::GetAssetInfo(){
}

