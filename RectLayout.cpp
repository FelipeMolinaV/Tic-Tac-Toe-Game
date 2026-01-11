#include "RectLayout.h"

#include <cassert>
#include <iostream>


RectLayout::RectLayout(int width, int height, int x, int y){
    mOriginalRect = {x, y, width, height};
    mTransformedRect = mOriginalRect;
    mPaddingX = 0;
    mPaddingY = 0;
}

RectLayout::RectLayout(int width, int height, int x, int y, int paddingX){
    mOriginalRect = {x, y, width, height};
    mTransformedRect = mOriginalRect;
    mPaddingX = 0;
    mPaddingY = 0;
    SetPaddingX(paddingX);
}

RectLayout::RectLayout(int width, int height, int x, int y, int paddingX, int paddingY){
    mOriginalRect = {x, y, width, height};
    mTransformedRect = mOriginalRect;
    mPaddingX = 0;
    mPaddingY = 0;
    SetPaddingX(paddingX);
    SetPaddingY(paddingY);
}

SDL_Point RectLayout::GetTopLeft(SDL_Point objectSize){
    return SDL_Point(mTransformedRect.x, mTransformedRect.y);
}

SDL_Point RectLayout::GetTopCenter(SDL_Point objectSize){
    return SDL_Point(mTransformedRect.x + mTransformedRect.w/2 - (objectSize.x/2), mTransformedRect.y);
}
SDL_Point RectLayout::GetTopRight(SDL_Point objectSize){
    return SDL_Point(mTransformedRect.x + mTransformedRect.w - objectSize.x, mTransformedRect.y);
}

SDL_Point RectLayout::GetMiddleLeft(SDL_Point objectSize){
    return SDL_Point(mTransformedRect.x, mTransformedRect.y + mTransformedRect.h/2 - (objectSize.y/2));
}

SDL_Point RectLayout::GetMiddleCenter(SDL_Point objectSize){
    return SDL_Point(mTransformedRect.x + mTransformedRect.w/2 - (objectSize.x/2), mTransformedRect.y + mTransformedRect.h/2 - (objectSize.y/2));
}

SDL_Point RectLayout::GetMiddleRight(SDL_Point objectSize){
    return SDL_Point(mTransformedRect.x + mTransformedRect.w - objectSize.x, mTransformedRect.y + mTransformedRect.h/2 - (objectSize.y/2));
}

SDL_Point RectLayout::GetBottomLeft(SDL_Point objectSize){
    return SDL_Point(mTransformedRect.x, mTransformedRect.y + mTransformedRect.h - objectSize.y);
}

SDL_Point RectLayout::GetBottomCenter(SDL_Point objectSize){
    return SDL_Point(mTransformedRect.x + mTransformedRect.w/2 - (objectSize.x/2), mTransformedRect.y + mTransformedRect.h - objectSize.y);
}

SDL_Point RectLayout::GetBottomRight(SDL_Point objectSize){
    return SDL_Point(mTransformedRect.x + mTransformedRect.w - objectSize.x, mTransformedRect.y + mTransformedRect.h - objectSize.y);
}

int RectLayout::GetWidth(){
    return mTransformedRect.w;
}

int RectLayout::GetHeight(){
    return mTransformedRect.h;
}

void RectLayout::SetPaddingX(int paddingX){
    mPaddingX = paddingX;
    mTransformedRect.x = mOriginalRect.x + mPaddingX;
    mTransformedRect.w = mOriginalRect.w - mPaddingX*2;
}

void RectLayout::SetPaddingY(int paddingY){
    mPaddingY = paddingY;
    mTransformedRect.y = mOriginalRect.y + mPaddingY;
    mTransformedRect.h = mOriginalRect.h - mPaddingY*2;
}


RectLayout RectLayout::CreateRectLayout(int widthPercentage, 
					int heightPercentage, 
					VerticalAlign vAlign, 
					HorizontalAlign hAlign)
{
    int w = ((float) widthPercentage/100) * (mTransformedRect.w);
    int h = ((float) heightPercentage/100) * (mTransformedRect.h);

    // Check for internal size capability
    
    // TOP-LEFT
    if (vAlign == TOP && hAlign == LEFT){
	return RectLayout(w, h, mTransformedRect.x, mTransformedRect.y); 	
    }
    // TOP-CENTER
    else if (vAlign == TOP && hAlign == CENTER){
	return RectLayout(w, h, mTransformedRect.x + mTransformedRect.w/2 - (w/2), mTransformedRect.y); 	
    }
    // TOP-RIGHT
    else if (vAlign == TOP && hAlign == RIGHT){
	return RectLayout(w, h, mTransformedRect.x + mTransformedRect.w - w, mTransformedRect.y); 	
    }
    // MIDDLE-LEFT
    else if (vAlign == MIDDLE && hAlign == LEFT){
	return RectLayout(w, h, mTransformedRect.x, mTransformedRect.y + mTransformedRect.h/2 - (h/2)); 	
    }
    // MIDDLE-CENTER
    else if (vAlign == MIDDLE && hAlign == CENTER){
	return RectLayout(w, h, mTransformedRect.x + mTransformedRect.w/2 - (w/2), mTransformedRect.y + mTransformedRect.h/2 - (h/2)); 	
    }
    // MIDDLE-RIGHT
    else if (vAlign == MIDDLE && hAlign == RIGHT){
	return RectLayout(w, h, mTransformedRect.x + mTransformedRect.w - w, mTransformedRect.y + mTransformedRect.h/2 - (h/2)); 	
    }
    // BOTTOM-LEFT
    else if (vAlign == BOTTOM && hAlign == LEFT){
	return RectLayout(w, h, mTransformedRect.x, mTransformedRect.y + mTransformedRect.h - h); 	
    }
    // BOTTOM-CENTER
    else if (vAlign == BOTTOM && hAlign == CENTER){
	return RectLayout(w, h, mTransformedRect.x + mTransformedRect.w/2 - (w/2), mTransformedRect.y + mTransformedRect.h - h); 	
    }
    // BOTTOM-RIGHT
    else {
	return RectLayout(w, h, mTransformedRect.x + mTransformedRect.w - w, mTransformedRect.y + mTransformedRect.h - h); 	
    }
}

RectLayout RectLayout::CreateRectLayout(int widthPercentage, 
					int heightPercentage, 
					VerticalAlign vAlign, 
					HorizontalAlign hAlign,
					int paddingX)
{
    auto newRectLayout = CreateRectLayout(widthPercentage, heightPercentage, vAlign, hAlign);
    newRectLayout.SetPaddingX(paddingX);
    return newRectLayout; 
}

RectLayout RectLayout::CreateRectLayout(int widthPercentage, 
					int heightPercentage, 
					VerticalAlign vAlign, 
					HorizontalAlign hAlign,
					int paddingX,
					int paddingY)
{
    auto newRectLayout = CreateRectLayout(widthPercentage, heightPercentage, vAlign, hAlign);
    newRectLayout.SetPaddingX(paddingX);
    newRectLayout.SetPaddingY(paddingY);
    return newRectLayout; 
}
