#include "GameScene.h"

void GameScene::OnEnter(){
    std::cout << "On enter Scene Game" << '\n';
}

void GameScene::Update(){
    
    if (mGame->GetKeystates()[SDL_SCANCODE_T]){
	std::cout << "Testing..." << '\n';
    }
}

void GameScene::OnExit(){
    std::cout << "On exit Scene Game" << '\n';
    RequestChangeScene(SceneType::SCENE_GAME);
}
