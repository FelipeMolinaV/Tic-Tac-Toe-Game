#include "Game.h"
#include "SceneManager.h"
#include "SceneType.h"

Game::Game(int w, int h) : width(w), height(h) {
    std::cout << "The game has been initialized" << '\n';
    #include "SceneManager.h"
}

Game::~Game(){
    SDL_DestroyWindow(mWindow);
    SDL_DestroyRenderer(mRenderer);
    delete mSceneManager;
    delete[] mKeystates;
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

    mSceneManager = new SceneManager(this);

    if (mSceneManager == nullptr){
	std::cout << "Failed to initialize Scene Manager" << '\n';
	return false;
    }
    else {
	mSceneManager->SetScene(SceneType::SCENE_GAME);
    }

    
    mKeystates = SDL_GetKeyboardState(nullptr);

    if (mKeystates == nullptr){
	std::cout << "Failed to get keyboard state" << '\n';
	return false;
    }

    mGameState = GameState::GAME_STATE_RUNNING;

    return true; 
}

SDL_Renderer* Game::GetRenderer(){
    return mRenderer;
}

GameState Game::GetGameState(){
    return mGameState;
}

void Game::SetGameState(GameState state){
    mGameState = state;
}

void Game::Run(){

    SDL_Event event;
    while (mGameState == GameState::GAME_STATE_RUNNING){
	while (SDL_PollEvent(&event)){
	    if (event.type == SDL_EVENT_QUIT){
		mGameState = GameState::GAME_STATE_STOPPED;	
		break;
	    }
	}

	mSceneManager->Tick();
    }
}

const bool* Game::GetKeystates(){
    return mKeystates;
}

