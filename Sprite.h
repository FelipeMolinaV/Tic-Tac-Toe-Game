#ifndef SPRITE_H
#define SPRITE_H

#include <SDL3/SDL.h>
#include <memory>

#include "Texture.h"
#include "GameObject.h"

class AssetFactory;

class Sprite : public GameObject {

public:

    Sprite(int gameObjectID, std::shared_ptr<Texture> texture);
    Sprite(int gameObjectID, std::shared_ptr<Texture> texture, SDL_Point size);
    Sprite(int gameObjectID, std::shared_ptr<Texture> texture, SDL_Point size, SDL_Point position);
    Sprite(int gameObjectID, std::shared_ptr<Texture> texture, SDL_Point size, SDL_Point position, int layer);
    Sprite(int gameObjectID, std::shared_ptr<Texture> texture, SDL_Point size, SDL_Point position, int layer, Uint8 alpha);

    void Render();

    void SetTexture(std::shared_ptr<Texture> texture);
    SDL_Point GetTextureSize();
    void SetTextureSize(int x, int y);

    void SetLayer(int layer);
    int GetLayer();

    void SetAlpha(Uint8 alpha);
    Uint8 GetAlpha();

    void SetVisibleState(bool state);
    bool GetVisibleState();

private:

    std::shared_ptr<Texture> mTexture; 
    SDL_Point mTextureSize;
    Uint8 mAlpha;
    bool mVisibleState;
    int mLayer;

};

#endif
