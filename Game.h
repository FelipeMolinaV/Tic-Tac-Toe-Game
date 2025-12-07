#ifndef GAME_H
#define GAME_H

#include <SDL3/SDL.h>
#include <iostream>

class SceneManager;

class Game{

public:

    Game(int w, int h);
    ~Game();
    bool Init();
    void Run();
    const bool* GetKeystates();

private:

    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;
    SceneManager* mSceneManager;
    int width;
    int height;
    bool running;
    const bool* mKeystates;
};

#endif 
