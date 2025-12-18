#ifndef GAME_H
#define GAME_H

#include <SDL3/SDL.h>
#include <iostream>
#include <memory>

#include "GameState.h"
#include "AssetManager.h"

class SceneManager;
class AssetManager;

class Game{

public:

    Game(int w, int h);
    ~Game();
    bool Init();
    void Run();
    SDL_Renderer* GetRenderer();
    GameState GetGameState();
    void SetGameState(GameState state);
    const bool* GetKeystates();
    std::shared_ptr<AssetManager> GetAssetManager();

    // TODO: Replace 
    SDL_Point GetWindowSize();

private:

    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;
    std::unique_ptr<SceneManager> mSceneManager;
    std::shared_ptr<AssetManager> mAssetManager;
    int width;
    int height;
    GameState mGameState;
    const bool* mKeystates;
};

#endif 
