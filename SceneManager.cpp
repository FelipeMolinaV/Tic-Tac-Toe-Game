#include <iostream>
#include <stdexcept>
#include <type_traits>
#include <vector>


#include "SceneManager.h"
#include "GameState.h"
#include "GameScene.h"
#include "SelectSideScene.h" 
#include "TestScene.h"
#include "Texture.h"
#include "FontAtlas.h"
#include "GameObject.h"
#include "CollisionSystem.h"
#include "Utils.h"

SceneManager::SceneManager(Game* game){
    // TODO: replace with throw 
    if (game == nullptr){
	throw std::runtime_error("Null pointer passed to game");
    }

    mGame = game;

    mSceneDataTransfer = std::make_shared<SceneDataTransfer>();
}

bool SceneManager::SetScene(SceneType type){

    // Set mouse in screen's center
    SDL_WarpMouseInWindow(mGame->GetWindow(), SCREEN_WIDTH/2, SCREEN_HEIGHT/2);

    switch (type){
	case SceneType::SCENE_SELECT_SIDE:
	    mCurrentScene = std::make_unique<SelectSideScene>(mGame, mSceneDataTransfer);
	    break;
	case SceneType::SCENE_GAME:
	    mCurrentScene = std::make_unique<GameScene>(mGame, mSceneDataTransfer); 
	    break;
	case SceneType::SCENE_TEST:
	    mCurrentScene = std::make_unique<TestScene>(mGame);
	    break;
	default:
	    return false;
    }

    mCurrentScene->RequestGameStateChange = [&](GameState state){
	mGame->SetGameState(state);
    };

    mCurrentScene->RequestInput = [&](std::function<void(SDL_Event)> function){
	SDL_Event event;
	while (SDL_PollEvent(&event)){
	   function(event); 
	}
    };

    mCurrentScene->RequestSceneChange = [&](SceneType type){
	mNextScene = type;
    };

    mCurrentScene->RequestRender = [&](std::function<void()> function){
	SDL_SetRenderDrawColor(mGame->GetRenderer(), 0, 0, 0, 255);
	SDL_RenderClear(mGame->GetRenderer());
	function();
	SDL_RenderPresent(mGame->GetRenderer());
    };

    mCurrentScene->RequestTexture = [&](int assetID){
	std::shared_ptr<Texture> texture = mGame->GetAssetManager()->GetAsset<Texture>(assetID);
	return texture;
    };

    mCurrentScene->RequestFontAtlas = [&](int assetID){
	std::shared_ptr<FontAtlas> fontAtlas = mGame->GetAssetManager()->GetAsset<FontAtlas>(assetID);
	return fontAtlas;
    };

    mCurrentScene->RequestAudio = [&](int assetID){
	std::shared_ptr<Audio> audio = mGame->GetAssetManager()->GetAsset<Audio>(assetID);
	return audio;
    };

    mCurrentScene->RequestCheckCollisions = [&](std::vector<std::shared_ptr<GameObject>> sprites){
	CheckCollisions(sprites);
    };

    mCurrentScene->OnEnter();
    return true;
}

void SceneManager::Tick(){

    mCurrentScene->Input();
    mCurrentScene->Update();
    mCurrentScene->Render();

    if (mNextScene.has_value()){
	mCurrentScene->OnExit();
	SetScene(mNextScene.value());
	mNextScene.reset();
    }
}


