#ifndef GAME_H
#define GAME_H

#include <SDL3/SDL.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <iostream>
#include <memory>

#include "GameState.h"
#include "AssetManager.h"
#include "GameObjectFactory.h"

class SceneManager;
class AssetManager;

class Game{

public:

    Game(int w, int h);
    ~Game();

    bool Init();
    void Run();

    SDL_Renderer* GetRenderer();
    MIX_Mixer* GetMixer();
    GameState GetGameState();
    void SetGameState(GameState state);
    const bool* GetKeystates();
    std::shared_ptr<AssetManager> GetAssetManager();
    std::shared_ptr<GameObjectFactory> GetGameObjectFactory();

    // TODO: Replace 
    SDL_Point GetWindowSize();

private:

    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;
    MIX_Mixer* mMixer;
    std::unique_ptr<SceneManager> mSceneManager;
    std::shared_ptr<AssetManager> mAssetManager;
    std::shared_ptr<GameObjectFactory> mGameObjectFactory;
    int width;
    int height;
    GameState mGameState;
    const bool* mKeystates;
};

#endif 
