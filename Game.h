#ifndef GAME_H
#define GAME_H

#include <SDL3/SDL.h>
#include <iostream>
#include <memory>

#include "GameState.h"

class SceneManager;

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

private:

    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;
    std::unique_ptr<SceneManager> mSceneManager;
    int width;
    int height;
    GameState mGameState;
    const bool* mKeystates;
};

#endif 
