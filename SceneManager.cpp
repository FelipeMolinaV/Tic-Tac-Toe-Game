#include "SceneManager.h"
#include "GameScene.h"
#include <iostream>
#include <stdexcept>
#include <type_traits>

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

    currentScene->RequestChangeScene = [&](SceneType type){
	this->SetScene(type);
    };

    currentScene->RequestSprite = [&](int assetId){

	std::shared_ptr<Sprite> sprite = mGame->GetAssetManager()->GetAsset<Sprite>(assetId);

	if (!sprite){
	    std::cout << "Failed to return sprite" << '\n';
	}

	return sprite;
    };

    currentScene->OnEnter();
    return true;
}

void SceneManager::Tick(){
    currentScene->Input();
    currentScene->Update();
    currentScene->Render();
}


