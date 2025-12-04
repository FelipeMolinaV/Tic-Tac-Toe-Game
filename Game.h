#ifndef GAME_H
#define GAME_H

#include <SDL3/SDL.h>
#include <iostream>

class Game{

public:

    Game(int w, int h);
    ~Game();
    bool Init();
    void Run();

private:

    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;
    int width;
    int height;
    bool running;
};

#endif 
