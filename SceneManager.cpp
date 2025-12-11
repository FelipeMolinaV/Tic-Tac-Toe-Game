#include "SceneManager.h"
#include "GameScene.h"
#include <iostream>

SceneManager::SceneManager(Game* game){
    if (game == nullptr){
	std::cout << "Failed to initialize the Scene Manager" << '\n';	
    }
    else {
	mGame = game;
    }
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


