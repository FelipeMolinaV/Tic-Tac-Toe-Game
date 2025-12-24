#include "GameScene.h"
#include <iostream>
#include <string>

#include "Asset.h"
#include "Sprite.h"
#include "GameState.h"

void GameScene::OnEnter(){
    std::cout << "On enter Scene Game" << '\n';

    // Request assets
    sprites["square1"] = RequestSprite(AssetID::ASSET_TEXTURE_SQUARE);
    sprites["square2"] = RequestSprite(AssetID::ASSET_TEXTURE_SQUARE);
    sprites["square3"] = RequestSprite(AssetID::ASSET_TEXTURE_SQUARE);
    sprites["square4"] = RequestSprite(AssetID::ASSET_TEXTURE_SQUARE);
    sprites["square5"] = RequestSprite(AssetID::ASSET_TEXTURE_SQUARE);
    sprites["square6"] = RequestSprite(AssetID::ASSET_TEXTURE_SQUARE);
    sprites["square7"] = RequestSprite(AssetID::ASSET_TEXTURE_SQUARE);
    sprites["square8"] = RequestSprite(AssetID::ASSET_TEXTURE_SQUARE);
    sprites["square9"] = RequestSprite(AssetID::ASSET_TEXTURE_SQUARE);
}

void GameScene::Input(){

    auto function = [&](SDL_Event event){

	if (event.type == SDL_EVENT_QUIT){
	    mGame->SetGameState(GameState::GAME_STATE_STOPPED);
	}

	if (event.type == SDL_EVENT_MOUSE_MOTION){
	    mousePosition.x = event.motion.x;
	    mousePosition.y = event.motion.y;
	}
    };

    RequestInput(function);
}

void GameScene::Update(){
    
    int rowIncrement = 0;
    int squareCount = 1;
    for (int row = 0; row < 3; row++){
	int colIncrement = 0;
	for (int col = 0; col < 3; col++){
	    std::string spriteKey = "square" + std::to_string(squareCount);
	    auto sprite = sprites[spriteKey]; 
	    sprite->SetSize(200, 200);
	    sprite->SetPosition(colIncrement + 640/2 + sprite->GetSize().x*col, rowIncrement + 360/8 + sprite->GetSize().y*row);    
	    colIncrement += 10;

	    if (sprite->IsColliding(mousePosition.x, mousePosition.y)){
		std::cout << "Is Colliding in square " << squareCount << std::endl;
	    }

	    squareCount++;
	}
	rowIncrement += 10;
    }
}

void GameScene::Render(){

    auto function = [&](){
	for (auto& [key, value] : sprites){
	    value->Render();
	}
    };

    RequestRender(function);
}

void GameScene::OnExit(){
    std::cout << "On exit Scene Game" << '\n';
    RequestChangeScene(SceneType::SCENE_GAME);
}
 
