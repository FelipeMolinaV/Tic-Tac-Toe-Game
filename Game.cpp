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
    else {
	SDL_SetRenderLogicalPresentation(mRenderer, width, height, SDL_LOGICAL_PRESENTATION_LETTERBOX);
    }

    mAssetManager = std::make_shared<AssetManager>(this);

    if (mAssetManager == nullptr){
	std::cout << "Failed to initialize Asset Manager" << '\n';
    }
    else {
	mAssetManager->LoadAssets("assets/assets.json");
    }
    
    mSceneManager = std::make_unique<SceneManager>(this); 

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

    if (!SDL_HideCursor()){
	std::cout << "Failed to hide cursor" << '\n';
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

std::shared_ptr<AssetManager> Game::GetAssetManager(){
    return mAssetManager;
}

SDL_Point Game::GetWindowSize(){
    return { width, height };
}

void Game::SetGameState(GameState state){
    mGameState = state;
}

void Game::Run(){
    while (mGameState == GameState::GAME_STATE_RUNNING){
	mSceneManager->Tick();
    }
}

const bool* Game::GetKeystates(){
    return mKeystates;
}

