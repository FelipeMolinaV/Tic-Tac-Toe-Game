#include "Text.h"

#include <utility>

Text::Text(std::shared_ptr<FontAtlas> fontAtlas, std::string& text, SDL_Color fg){
    mFontAtlas = fontAtlas;
    mText = text;
    mForegroundColor = fg;
    mVisibleState = true;
    SetCollisionState(true);
}

Text::Text(std::shared_ptr<FontAtlas> fontAtlas, std::string& text, SDL_Color fg, SDL_Point size)
    : GameObject(size)
{
    mFontAtlas = fontAtlas;
    mText = text;
    mForegroundColor = fg;
    mVisibleState = true;
    SetCollisionState(true);
}

Text::Text(std::shared_ptr<FontAtlas> fontAtlas, std::string& text, SDL_Color fg, SDL_Point size, SDL_Point position)
    : GameObject(size, position)
{
    mFontAtlas = fontAtlas;
    mText = text;
    mForegroundColor = fg;
    mVisibleState = true;
    SetCollisionState(true);
}

Text::Text(std::shared_ptr<FontAtlas> fontAtlas, std::string& text, SDL_Color fg, SDL_Point size, SDL_Point position, int layer)
    : GameObject(size, position)
{
    mFontAtlas = fontAtlas;
    mText = text;
    mForegroundColor = fg;
    mVisibleState = true;
    SetCollisionState(true);
    mLayer = layer;
}

Text::Text(std::shared_ptr<FontAtlas> fontAtlas, std::string& text, SDL_Color fg, SDL_Point size, SDL_Point position, int layer, int alpha)
    : GameObject(size, position)
{
    mFontAtlas = fontAtlas;
    mText = text;
    mForegroundColor = fg;
    mVisibleState = true;
    SetCollisionState(true);
    mLayer = layer;
    mAlpha = alpha;
}

Text& Text::operator=(Text&& other){
    if (this != &other){

	this->mSize = std::move(other.mSize);
	this->mPosition = std::move(other.mPosition);
	this->mFontAtlas =  std::move(other.mFontAtlas);
	this->mText =  std::move(other.mText);
	this->mForegroundColor =  std::move(other.mForegroundColor);
	this->mVisibleState =  std::move(other.mVisibleState);
	this->mLayer =  std::move(other.mLayer);
	this->mAlpha =  std::move(other.mAlpha);
    }

    return *this;
}

Text::Text(Text&& other)
: GameObject(std::move(other))
{
    *this = std::move(other);
}

void Text::SetText(std::string text){
    mText = text;
}

std::string& Text::GetText(){
    return mText;
}

void Text::Render(){
    if (GetActive()){
	mFontAtlas->RenderText(mSize, mPosition, mText, mAlpha); 
    }
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

