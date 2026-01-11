#ifndef RECTLAYOUT_H
#define RECTLAYOUT_H

#include <SDL3/SDL.h>
#include <vector>

enum HorizontalAlign{
    LEFT,
    CENTER,
    RIGHT
};

enum VerticalAlign{
    TOP,
    MIDDLE,
    BOTTOM
};

class RectLayout{

public:

    RectLayout(int width, int height, int x, int y);
    RectLayout(int width, int height, int x, int y, int paddingX);
    RectLayout(int width, int height, int x, int y, int paddingX, int paddingY);

    SDL_Point GetTopLeft(SDL_Point objectSize);
    SDL_Point GetTopCenter(SDL_Point objectSize);
    SDL_Point GetTopRight(SDL_Point objectSize);

    SDL_Point GetMiddleLeft(SDL_Point objectSize);
    SDL_Point GetMiddleCenter(SDL_Point objectSize);
    SDL_Point GetMiddleRight(SDL_Point objectSize);

    SDL_Point GetBottomLeft(SDL_Point objectSize);
    SDL_Point GetBottomCenter(SDL_Point objectSize);
    SDL_Point GetBottomRight(SDL_Point objectSize);

    int GetWidth();
    int GetHeight();

    void SetPaddingX(int paddingX);
    void SetPaddingY(int paddingY);

    RectLayout CreateRectLayout(int widthPercentage, int heightPercentage, VerticalAlign vAlign, HorizontalAlign hAlign);
    RectLayout CreateRectLayout(int widthPercentage, int heightPercentage, VerticalAlign vAlign, HorizontalAlign hAlign, int paddingX);
    RectLayout CreateRectLayout(int widthPercentage, int heightPercentage, VerticalAlign vAlign, HorizontalAlign hAlign, int paddingX, int paddingY);


private:

    SDL_Rect mOriginalRect;
    SDL_Rect mTransformedRect;
    int mPaddingX;
    int mPaddingY;
};

#endif
