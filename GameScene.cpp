#include "GameScene.h"
#include <iostream>
#include <string>
#include <cmath>
#include <utility>
#include <cstdlib>
#include <time.h>

#include "Asset.h"
#include "Sprite.h"
#include "GameState.h"
#include "AIController.h"
#include "Utils.h"

enum class GameScene::Layers{
    BACKGROUND,
    GRID,
    EFFECT,
    SYMBOLS,
    CURSOR,
    COUNT
};

void GameScene::GenerateGrid(int widthGap, int heightGap){

    // TODO: Add tools to get the screen's center or key positions
    int screenWidth = 640;
    int screenHeight = 360;

    int i = 1;
    int rowIncrement = 0;

    for (int row = 0; row < 3; row++){

	int colIncrement = 0;

	for (int col = 0; col < 3; col++){

	    // Define cellId with square's game object id 
	    mGameData.board[row][col]->cellID = i; 

	    // sprites grid
	    std::string key = "square" + std::to_string(i);
	    sprites[key] = RequestSprite(AssetID::ASSET_TEXTURE_SQUARE);
	    sprites[key]->SetSize(200, 200);
	    sprites[key]->SetTextureSize(200, 200);
	    sprites[key]->SetLayer(static_cast<int>(Layers::GRID));

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

    // Config Players data

    mPlayer = {'X', PlayerType::PLAYER_TYPE_HUMAN};
    mAdversary = {'O', PlayerType::PLAYER_TYPE_AI};

    mCurrentPlayer = mPlayer;

    // Initialize AIController
    //
    mAIController = std::make_unique<AIController>(
	GenerateTerminalFunction(),
	GenerateEvaluateStateFunction(mAdversary.symbol, mPlayer.symbol),
	GenerateSuccessionFunction(mAdversary.symbol, mPlayer.symbol));

    // Initialize grid
    GenerateGrid(20, 20);
    
    sprites["cursor_cross"] = RequestSprite(AssetID::ASSET_TEXTURE_CROSS);
    sprites["cursor_cross"]->SetSize(200, 200);
    sprites["cursor_cross"]->SetTextureSize(200, 200);
    sprites["cursor_cross"]->SetVisibleState(false);
    sprites["cursor_cross"]->SetPosition(0, 0);
    sprites["cursor_cross"]->SetCollisionState(false);
    sprites["cursor_cross"]->SetAlpha(70);
    sprites["cursor_cross"]->SetLayer(static_cast<int>(Layers::EFFECT));
    
    for (auto& [key, value] : sprites){
	if (key.substr(0, 6) == "square"){

	    value->SetSize(200, 200);
	    value->SetTextureSize(200, 200);

	    value->OnStay = [&](std::shared_ptr<GameObject> cursorCrossObj){

		for (int row = 0; row < 3; row++){
		    for (int col = 0; col < 3; col++){
			if (value->GetGameObjectID() == mGameData.board[row][col]->cellID && mGameData.board[row][col]->available){
			    sprites["cursor_cross"]->SetVisibleState(true);
			    sprites["cursor_cross"]->SetPosition(value->GetPosition().x, value->GetPosition().y);
			}
		    }
		}
	    };

	    value->OnClick = [&](){

		auto getCell = [&](int gameObjectID) -> std::shared_ptr<Cell> {
		    for (int row = 0; row < 3; row++){
			for (int col = 0; col < 3; col++){
			    if (mGameData.board[row][col]->cellID == gameObjectID){
				return mGameData.board[row][col];
			    }
			}
		    }

		    return nullptr;
		};

		auto cell = getCell(value->GetGameObjectID());

		if (cell != nullptr && cell->available){

		    std::cout << "New cross" << std::endl;

		    sprites["cursor_cross"]->SetVisibleState(false);

		    cell->symbol = mCurrentPlayer.symbol;
		    cell->available = false;

		    std::string key = "cross" + std::to_string(value->GetGameObjectID());
		    std::shared_ptr<Sprite> sprite = RequestSprite(AssetID::ASSET_TEXTURE_CROSS);
		    sprite->SetSize(200, 200);
		    sprite->SetTextureSize(200, 200);
		    sprite->SetPosition(value->GetPosition().x, value->GetPosition().y);
		    sprite->SetCollisionState(false);
		    sprite->SetLayer(static_cast<int>(Layers::SYMBOLS));
		    pendingSprites.push_back({key, sprite});

		    // Change current Player
		    mCurrentPlayer = mAdversary;

		}

	    };

	    value->OnExit = [&](std::shared_ptr<GameObject> cursorCrossObj){
		sprites["cursor_cross"]->SetVisibleState(false);
	    };
	}
    }
    
    sprites["cursor"] = RequestSprite(AssetID::ASSET_TEXTURE_CURSOR);
    sprites["cursor"]->SetSize(20, 20);
    sprites["cursor"]->SetTextureSize(40, 40);
    sprites["cursor"]->SetQueryOnly(true);
    sprites["cursor"]->SetLayer(static_cast<int>(Layers::CURSOR));
    
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

	if (mCurrentPlayer.type == PlayerType::PLAYER_TYPE_HUMAN){

	    if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN){

		const auto& collidingObj = sprites["cursor"]->GetCollidingGameObject(); 

		if (collidingObj != nullptr) {
		    if ( collidingObj->OnClick != nullptr ) {
			collidingObj->OnClick();	
		    }
		}
	    }
	}

	if (event.type == SDL_EVENT_KEY_DOWN){
	    if (event.key.key == SDLK_M){
		for (int row = 0; row < 3; row++){
		    for (int col = 0; col < 3; col++){
			if (mGameData.board[row][col]->available){
			    std::cout << "* ";
			    continue;
			}
			std::cout << mGameData.board[row][col]->symbol << " ";
		    }
		    std::cout << std::endl;
		}
	    }
	}

    };

    RequestInput(function);
}

void GameScene::Update(){

    if (GetTicTacToeWinner(mGameData.board) != ' '){
	timer.StartTimer(500, [&](){
	    OnExit();
	    return;
	});
    }
    else{

	sprites["cursor"]->SetPosition(mousePosition.x, mousePosition.y);
	
	if (mCurrentPlayer.type == PlayerType::PLAYER_TYPE_HUMAN){

	    std::vector<std::shared_ptr<GameObject>> collidables;
	    for (auto& [key, value] : sprites){
		if (value->GetCollisionState()){
		    collidables.push_back(value);
		}
	    }

	    RequestCheckCollisions(collidables);
	}
	else {

	    auto aiPlay= [&](){

		State state;

		for (int row = 0; row < 3; row++){
		    for (int col = 0; col < 3; col++){
			state.board[row][col] = mGameData.board[row][col];
		    }
		}

		std::pair<int, int> coordinates = mAIController->GetBestMove(state);

		mGameData.board[coordinates.first][coordinates.second]->symbol = mCurrentPlayer.symbol; 
		mGameData.board[coordinates.first][coordinates.second]->available = false;

		// TODO: add matrix square position on struct 

		std::string key = "circle" + std::to_string(mGameData.board[coordinates.first][coordinates.second]->cellID);
		std::shared_ptr<Sprite> sprite = RequestSprite(AssetID::ASSET_TEXTURE_CIRCLE);
		sprite->SetSize(200, 200);
		sprite->SetTextureSize(200, 200);
		std::string squareKey = "square" + std::to_string(mGameData.board[coordinates.first][coordinates.second]->cellID);
		sprite->SetPosition(sprites[squareKey]->GetPosition().x, sprites[squareKey]->GetPosition().y);
		sprite->SetCollisionState(false);
		sprite->SetLayer(static_cast<int>(Layers::SYMBOLS));
		pendingSprites.push_back({key, sprite});

		mCurrentPlayer = mPlayer;

		sprites["cursor_cross"]->SetVisibleState(true);
	    };

	    timer.StartTimer(1000, aiPlay); 
	}

	for (auto& pendingSprite : pendingSprites){
	    sprites[pendingSprite.first] = pendingSprite.second;
	}

	pendingSprites.clear();
    }

}

void GameScene::Render(){

    auto function = [&](){
	
	for (int layer = 0; layer < static_cast<int>(Layers::COUNT); layer++){
	    for (const auto& [key, value] : sprites){
		if (value->GetLayer() == layer){
		    value->Render();
		}
	    }
	}
    };

    RequestRender(function);
}

void GameScene::OnExit(){
    std::cout << "On exit Scene Game" << '\n';
    sprites.clear();
    pendingSprites.clear();
    RequestChangeScene(SceneType::SCENE_GAME);
}
 
