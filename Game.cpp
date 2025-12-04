#include "Game.h"

Game::Game(int w, int h) : width(w), height(h) {
    std::cout << "The game has been initialized" << '\n';
}

Game::~Game(){
    SDL_DestroyWindow(mWindow);
    SDL_DestroyRenderer(mRenderer);
    SDL_Quit();
}

bool Game::Init(){

    if (!SDL_Init(SDL_INIT_VIDEO)){
	std::cout << "Failed to initialized SDL3" << '\n';
	return false;
    }

    mWindow = SDL_CreateWindow(
	"Tic Tac Toe",
	width,
	height,
	SDL_WINDOW_RESIZABLE
    );

    if (mWindow == nullptr){
	std::cout << "Failed to create a window" << '\n';
	return false;
    }
    
    mRenderer = SDL_CreateRenderer(mWindow, nullptr);

    if (mRenderer == nullptr){
	std::cout << "Failed to create a renderer" << '\n';
	return false;
    }

    return true; 
}

void Game::Run(){
   
    while (running){
	
	SDL_Event event;

	while (SDL_PollEvent(&event)){
	    if (event.type == SDL_EVENT_QUIT){
		running = false;
	    }
	}

	SDL_RenderClear(mRenderer);
	SDL_SetRenderDrawColor(mRenderer, 191, 191, 191, 255);
	SDL_RenderPresent(mRenderer);
    }

}
