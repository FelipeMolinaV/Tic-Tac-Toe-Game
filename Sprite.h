#ifndef SPRITE_H
#define SPRITE_H

#include <SDL3/SDL.h>
#include <memory>

#include "Texture.h"
#include "Renderable.h"
#include "GameObject.h"

class AssetFactory;

class Sprite : public GameObject, public Renderable {

public:

    Sprite(std::shared_ptr<Texture> texture);
    Sprite(std::shared_ptr<Texture> texture, SDL_Point size);
    Sprite(std::shared_ptr<Texture> texture, SDL_Point size, SDL_Point position);
    Sprite(std::shared_ptr<Texture> texture, SDL_Point size, SDL_Point position, int layer);
    Sprite(std::shared_ptr<Texture> texture, SDL_Point size, SDL_Point position, int layer, int alpha);

    // sprite's functions
    void SetTexture(std::shared_ptr<Texture> texture);
    SDL_Point GetTextureSize();
    void SetTextureSize(int x, int y);

    // Renderable's virtual functions
    void Render() override;
    void SetLayer(int layer) override;
    int GetLayer() override;

    void SetAlpha(int alpha) override;
    int GetAlpha() override;

    void SetVisibleState(bool state) override;
    bool GetVisibleState() override;

    static constexpr const char* TypeName = "Sprite";

private:

    std::shared_ptr<Texture> mTexture; 
    SDL_Point mTextureSize;
    int mAlpha;
    bool mVisibleState;
    int mLayer;

};

#endif
