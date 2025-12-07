#include "SceneManager.h"
#include <iostream>

SceneManager::SceneManager(Game* game){
    if (game == nullptr){
	std::cout << "Failed to initialize the Scene Manager" << '\n';	
    }
    else {
	mGame = game;
    }
}

SceneManager::~SceneManager(){
    mGame = nullptr;
}

bool SceneManager::SetScene(SceneType type){

    switch (type){
	case SceneType::SCENE_GAME:
	    delete currentScene;
	    //currentScene = new GameScene();
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

void SceneManager::Update(){
    currentScene->Update();
}
