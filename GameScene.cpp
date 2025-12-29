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

    sprites["cursor_cross"] = RequestSprite(AssetID::ASSET_TEXTURE_CROSS);
    sprites["cursor_cross"]->SetSize(200, 200);
    sprites["cursor_cross"]->SetTextureSize(200, 200);
    sprites["cursor_cross"]->SetVisibleState(false);
    sprites["cursor_cross"]->SetPosition(0, 0);
    sprites["cursor_cross"]->SetCollisionState(false);
    
    for (auto& [key, value] : sprites){
	if (key.substr(0, 6) == "square"){

	    value->SetSize(200, 200);
	    value->SetTextureSize(200, 200);

	    value->OnStay = [&](std::shared_ptr<GameObject> cursorCrossObj){
		sprites["cursor_cross"]->SetVisibleState(true);
		sprites["cursor_cross"]->SetPosition(value->GetPosition().x, value->GetPosition().y);
	    };

	    value->OnExit = [&](std::shared_ptr<GameObject> cursorCrossObj){
		sprites["cursor_cross"]->SetVisibleState(false);
	    };

	    value->OnClick = [&](){
		if (value->HasCollision(sprites["cursor"]->GetGameObjectID())){
		    std::cout << "On Click: " << value->GetGameObjectID() << std::endl;
		}
	    };
	}
    }
    
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
	rowIncrement += 20;
    }

    sprites["cursor"] = RequestSprite(AssetID::ASSET_TEXTURE_CURSOR);
    sprites["cursor"]->SetSize(10, 10);
    sprites["cursor"]->SetTextureSize(20, 20);
    sprites["cursor"]->SetQueryOnly(true);
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

	if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN){

	    for (const auto& [key, value] : sprites){

		if (value->OnClick == nullptr){
		    continue;
		}

		value->OnClick();
	    }
	}
    };

    RequestInput(function);
}

void GameScene::Update(){

    auto& cursor = sprites["cursor"];
    cursor->SetPosition(mousePosition.x - (cursor->GetSize().x/2) , mousePosition.y - (cursor->GetSize().y/2));

    RequestCheckCollisions(sprites);
}

void GameScene::Render(){

    auto function = [&](){
	for (auto& [key, value] : sprites){
	    if (key.substr(0, 6) == "square"){
		value->Render();
	    }
	}
	
	sprites["cursor_cross"]->Render(80);
	sprites["cursor"]->Render();
    };

    RequestRender(function);
}

void GameScene::OnExit(){
    std::cout << "On exit Scene Game" << '\n';
    RequestChangeScene(SceneType::SCENE_GAME);
}
 
