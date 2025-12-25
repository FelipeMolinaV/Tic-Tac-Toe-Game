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

    for (auto& [key, value] : sprites){
	if (key != "cursor"){

	    value->SetSize(200, 200);
	    value->SetTextureSize(200, 200);
	    
	    value->OnEnter = [&](){
		value->SetTextureSize(150, 150);
	    };
	    value->OnExit = [&](){
		value->SetTextureSize(200, 200);
	    };
	}
    }

    sprites["cursor"] = RequestSprite(AssetID::ASSET_TEXTURE_CURSOR);
    sprites["cursor"]->SetSize(25, 25);
    sprites["cursor"]->OnEnter = nullptr;
    sprites["cursor"]->OnExit = nullptr;
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
	    sprite->SetPosition(colIncrement + 640/2 + 200*col, rowIncrement + 360/8 + 200*row);    
	    colIncrement += 20;
	    squareCount++;
	}
	rowIncrement += 10;
    }

    auto& cursor = sprites["cursor"];
    cursor->SetPosition(mousePosition.x - (cursor->GetSize().x/2) , mousePosition.y - (cursor->GetSize().y/2));

    RequestCheckCollisions(sprites);
}

void GameScene::Render(){

    auto function = [&](){
	for (auto& [key, value] : sprites){
	    if (key != "cursor"){
		value->Render();
	    }
	}
	sprites["cursor"]->Render();
    };

    RequestRender(function);
}

void GameScene::OnExit(){
    std::cout << "On exit Scene Game" << '\n';
    RequestChangeScene(SceneType::SCENE_GAME);
}
 
