#include "SceneManager.h"
#include "GameScene.h"
#include <iostream>
#include <stdexcept>

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

    currentScene->OnEnter();
    return true;
}

void SceneManager::Tick(){
    currentScene->Input();
    currentScene->Update();
    currentScene->Render();
}


