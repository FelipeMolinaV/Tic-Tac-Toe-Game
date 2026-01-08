#include "SceneManager.h"
#include "GameScene.h"
#include <iostream>
#include <stdexcept>
#include <type_traits>
#include <vector>

#include "GameState.h"
#include "Texture.h"
#include "FontAtlas.h"
#include "GameObject.h"
#include "CollisionSystem.h"

SceneManager::SceneManager(Game* game){
    // TODO: replace with throw 
    if (game == nullptr){
	throw std::runtime_error("Null pointer passed to game");
    }

    mGame = game;
}

bool SceneManager::SetScene(SceneType type){

    switch (type){
	case SceneType::SCENE_GAME:
	    currentScene = std::make_unique<GameScene>(mGame); 
	    break;
	default:
	    return false;
    }

    currentScene->RequestGameStateChange = [&](GameState state){
	mGame->SetGameState(state);
    };

    currentScene->RequestInput = [&](std::function<void(SDL_Event)> function){
	SDL_Event event;
	while (SDL_PollEvent(&event)){
	   function(event); 
	}
    };

    currentScene->RequestSceneChange = [&](SceneType type){
	nextScene = type;
    };

    currentScene->RequestRender = [&](std::function<void()> function){
	SDL_RenderClear(mGame->GetRenderer());
	SDL_SetRenderDrawColor(mGame->GetRenderer(), 0, 0, 0, 255);
	function();
	SDL_RenderPresent(mGame->GetRenderer());
    };

    currentScene->RequestTexture = [&](int assetID){
	std::shared_ptr<Texture> texture = mGame->GetAssetManager()->GetAsset<Texture>(assetID);
	return texture;
    };

    currentScene->RequestFontAtlas = [&](int assetID){
	std::shared_ptr<FontAtlas> fontAtlas = mGame->GetAssetManager()->GetAsset<FontAtlas>(assetID);
	return fontAtlas;
    };
    currentScene->RequestCheckCollisions = [&](std::vector<std::shared_ptr<GameObject>> sprites){
	CheckCollisions(sprites);
    };

    currentScene->OnEnter();
    return true;
}

void SceneManager::Tick(){

    currentScene->Input();
    currentScene->Update();
    currentScene->Render();

    if (nextScene.has_value()){
	currentScene->OnExit();
	SetScene(nextScene.value());
	nextScene.reset();
    }
}


