#include "Text.h"

Text::Text(std::shared_ptr<Font> font, std::string& text, SDL_Color fg){
    mFont = font;
    mText = text;
    mForegroundColor = fg;
    mVisibleState = true;
    SetCollisionState(true);
}

Text::Text(std::shared_ptr<Font> font, std::string& text, SDL_Color fg, SDL_Point size)
    : GameObject(size)
{
    mFont = font;
    mText = text;
    mForegroundColor = fg;
    mVisibleState = true;
    SetCollisionState(true);
}

Text::Text(std::shared_ptr<Font> font, std::string& text, SDL_Color fg, SDL_Point size, SDL_Point position)
    : GameObject(size, position)
{
    mFont = font;
    mText = text;
    mForegroundColor = fg;
    mVisibleState = true;
    SetCollisionState(true);
}

Text::Text(std::shared_ptr<Font> font, std::string& text, SDL_Color fg, SDL_Point size, SDL_Point position, int layer)
    : GameObject(size, position)
{
    mFont = font;
    mText = text;
    mForegroundColor = fg;
    mVisibleState = true;
    SetCollisionState(true);
    mLayer = layer;
}

Text::Text(std::shared_ptr<Font> font, std::string& text, SDL_Color fg, SDL_Point size, SDL_Point position, int layer, int alpha)
    : GameObject(size, position)
{
    mFont = font;
    mText = text;
    mForegroundColor = fg;
    mVisibleState = true;
    SetCollisionState(true);
    mLayer = layer;
    mAlpha = alpha;
}

Text::~Text(){
    if (mTexture != nullptr){
	SDL_DestroyTexture(mTexture);
    }
}

void Text::SetText(std::string& text){

    // Destroy mTexture then get nullptr on Render's condition to create a new texture
    if (mTexture != nullptr){
	SDL_DestroyTexture(mTexture);
    }

    mText = text;
}
std::string& Text::GetText(){
    return mText;
}

void Text::Render(){

    mFont->RenderText(mTexture, mSize, mPosition, mText, 0, mForegroundColor, mAlpha); 
}

void Text::SetLayer(int layer){
    mLayer = layer;
}

int Text::GetLayer(){
    return mLayer;
}

void Text::SetAlpha(int alpha){
    mAlpha = alpha;
}

int Text::GetAlpha(){
    return mAlpha;
}

void Text::SetVisibleState(bool state){
    mVisibleState = state;
}

bool Text::GetVisibleState(){
    return mVisibleState;
}

