#ifndef TEXT_H
#define TEXT_H

#include <SDL3/SDL.h>
#include <memory>
#include <string>

#include "GameObject.h"
#include "Renderable.h"
#include "Font.h"

class Text : public GameObject, public Renderable {

public:

    Text(std::shared_ptr<Font> font, std::string& text, SDL_Color fg);
    Text(std::shared_ptr<Font> font, std::string& text, SDL_Color fg, SDL_Point size);
    Text(std::shared_ptr<Font> font, std::string& text, SDL_Color fg, SDL_Point size, SDL_Point position);
    Text(std::shared_ptr<Font> font, std::string& text, SDL_Color fg, SDL_Point size, SDL_Point position, int layer);
    Text(std::shared_ptr<Font> font, std::string& text, SDL_Color fg, SDL_Point size, SDL_Point position, int layer, int alpha);
    ~Text();
    
    // Text's functions
    void SetText(std::string& text);
    std::string& GetText();

    // Renderable's virtual functions
    void Render() override;
    void SetLayer(int layer) override;
    int GetLayer() override;

    void SetAlpha(int alpha) override;
    int GetAlpha() override;

    void SetVisibleState(bool state) override;
    bool GetVisibleState() override;
    
    static constexpr const char* TypeName = "Text";

private:

    SDL_Texture* mTexture;

    std::shared_ptr<Font> mFont;
    std::string mText;
    SDL_Color mForegroundColor;
    bool mVisibleState;
    int mLayer;
    int mAlpha;
};

#endif
