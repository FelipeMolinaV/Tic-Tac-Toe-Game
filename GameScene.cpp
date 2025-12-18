#include "GameScene.h"
#include <iostream>

#include "Asset.h"
#include "Sprite.h"

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

    SDL_RenderClear(mGame->GetRenderer());
    SDL_SetRenderDrawColor(mGame->GetRenderer(), 0, 0, 0, 255);
    
    for (int row = 0; row < 2; row++){
	for (int col = 0; col < 4; col++){
	    std::shared_ptr<Sprite> sprite = std::dynamic_pointer_cast<Sprite>(mGame->GetAssetManager()->GetAsset("sprite1"));
	    sprite->SetPosition((mGame->GetWindowSize().x/4)*col, (mGame->GetWindowSize().y/2)*row);    
	    sprite->RenderSprite();
	}
    }
    SDL_RenderPresent(mGame->GetRenderer());
}

void GameScene::OnExit(){
    std::cout << "On exit Scene Game" << '\n';
    RequestChangeScene(SceneType::SCENE_GAME);
}
 
