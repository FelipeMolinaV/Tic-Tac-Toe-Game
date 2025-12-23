#include "GameScene.h"
#include <iostream>

#include "Asset.h"
#include "Sprite.h"

void GameScene::OnEnter(){
    std::cout << "On enter Scene Game" << '\n';

    // Request assets
    sprites["square"] = RequestSprite(AssetID::ASSET_SPRITE_SQUARE);
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

    int rowIncrement = 0;
    for (int row = 0; row < 3; row++){
	int colIncrement = 0;
	for (int col = 0; col < 3; col++){
	    auto sprite = sprites["square"]; 
	    sprite->SetPosition(colIncrement + 640/2 + sprite->GetSize().x*col, rowIncrement + 360/8 + sprite->GetSize().y*row);    
	    sprite->RenderSprite();
	    colIncrement += 10;
	}
	rowIncrement += 10;

    }
    SDL_RenderPresent(mGame->GetRenderer());
}

void GameScene::OnExit(){
    std::cout << "On exit Scene Game" << '\n';
    RequestChangeScene(SceneType::SCENE_GAME);
}
 
