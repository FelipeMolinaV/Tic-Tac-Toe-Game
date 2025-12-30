#include "GameScene.h"
#include <iostream>
#include <string>
#include <cmath>

#include "Asset.h"
#include "Sprite.h"
#include "GameState.h"

void GameScene::GenerateGrid(int widthGap, int heightGap){

    // TODO: Add tools to get the screen's center or key positions
    int screenWidth = 640;
    int screenHeight = 360;

    int i = 1;
    int rowIncrement = 0;

    for (int row = 0; row < 3; row++){

	int colIncrement = 0;

	for (int col = 0; col < 3; col++){

	    // matrix data
	    grid[row][col] = std::make_shared<CellData>(true, i); 

	    // sprites grid
	    std::string key = "square" + std::to_string(i);
	    sprites[key] = RequestSprite(AssetID::ASSET_TEXTURE_SQUARE);
	    sprites[key]->SetSize(200, 200);
	    sprites[key]->SetTextureSize(200, 200);

	    int spriteWidth = sprites[key]->GetSize().x;
	    int spriteHeight = sprites[key]->GetSize().y;

	    sprites[key]->SetPosition(
		(screenWidth*0.5) + (spriteWidth*col) + colIncrement, 
		(screenHeight/8) + spriteHeight*row + rowIncrement);    

	    i++;
	    colIncrement += widthGap;
	}
	rowIncrement += heightGap;
    }
}

void GameScene::OnEnter(){

    std::cout << "On enter Scene Game" << '\n';

    // Initialize grid
    GenerateGrid(20, 20);
    
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

	    value->OnClick = [&](){

		auto getCell = [&](int gameObjectID) -> std::shared_ptr<CellData> {

		    for (int row = 0; row < 3; row++){
			for (int col = 0; col < 3; col++){
			    if (grid[row][col]->gameObjectID == gameObjectID){
				return grid[row][col];
			    }
			}
		    }
		    return nullptr;
		};

		auto cell = getCell(value->GetGameObjectID());

		if (cell != nullptr && cell->state){

		    std::cout << "New cross" << std::endl;

		    cell->state = false;

		    std::string key = "cross" + std::to_string(value->GetGameObjectID());
		    std::shared_ptr<Sprite> sprite = RequestSprite(AssetID::ASSET_TEXTURE_CROSS);
		    sprite->SetSize(200, 200);
		    sprite->SetTextureSize(200, 200);
		    sprite->SetPosition(value->GetPosition().x, value->GetPosition().y);
		    sprite->SetCollisionState(false);
		    pendingSprites.push_back({key, sprite});
		}

	    };

	    value->OnExit = [&](std::shared_ptr<GameObject> cursorCrossObj){
		sprites["cursor_cross"]->SetVisibleState(false);
	    };
	}
    }
    
    sprites["cursor"] = RequestSprite(AssetID::ASSET_TEXTURE_CURSOR);
    sprites["cursor"]->SetSize(20, 20);
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

	    const auto& collidingObj = sprites["cursor"]->GetCollidingGameObject(); 

	    if (collidingObj != nullptr ) {
		if ( collidingObj->OnClick != nullptr ) {
		    collidingObj->OnClick();	
		}
	    }
	}
    };

    RequestInput(function);
}

void GameScene::Update(){

    sprites["cursor"]->SetPosition(mousePosition.x, mousePosition.y);

    std::vector<std::shared_ptr<GameObject>> collidables;
    for (auto& [key, value] : sprites){
	if (value->GetCollisionState()){
	    collidables.push_back(value);
	}
    }

    RequestCheckCollisions(collidables);
    
}

void GameScene::Render(){

    auto function = [&](){
	
	for (auto& [key, value] : sprites){
	    if (key.substr(0, 6) == "square"){
		value->Render();
	    }
	}

	for (auto& [key, value] : sprites){
	    if (key.substr(0, 5) == "cross"){
		value->Render();
	    }
	}
	
	sprites["cursor_cross"]->Render(80);
	sprites["cursor"]->Render();
    };

    RequestRender(function);

    for (auto& pendingSprite : pendingSprites){
	sprites[pendingSprite.first] = pendingSprite.second;
    }

    pendingSprites.clear();
}

void GameScene::OnExit(){
    std::cout << "On exit Scene Game" << '\n';
    RequestChangeScene(SceneType::SCENE_GAME);
}
 
