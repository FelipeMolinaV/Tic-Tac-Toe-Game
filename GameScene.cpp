#include "GameScene.h"
#include <iostream>

void GameScene::OnEnter(){
    std::cout << "On enter Scene Game" << '\n';
}

void GameScene::Input(){
    if (mGame->GetKeystates()[SDL_SCANCODE_T]){
	std::cout << "Testing..." << '\n';
    }
    if (mGame->GetKeystates()[SDL_SCANCODE_E]){
	OnExit();
    }
}

void GameScene::Update(){
    
}

void GameScene::Render(){
}

void GameScene::OnExit(){
    std::cout << "On exit Scene Game" << '\n';
    RequestChangeScene(SceneType::SCENE_GAME);
}
