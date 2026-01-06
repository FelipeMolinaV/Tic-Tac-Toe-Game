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
#include "GameScene.h"
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

    int rowIncrement = 0;

    int i = 0;
    for (int row = 0; row < 3; row++){

	int colIncrement = 0;

	for (int col = 0; col < 3; col++){


	    // Define cellId with square's game object id 

	    std::string key = "square" + std::to_string(i);
	    auto square = Create<Sprite>(key, 
					 RequestTexture(AssetID::ASSET_TEXTURE_SQUARE), 
				         SDL_Point(200, 200), 
					 SDL_Point(0, 0),
					 static_cast<int>(Layers::GRID),
					 255);
	    square->SetTextureSize(200, 200);

	    mGameData.board[row][col]->cellID = square->GetGameObjectID(); 

	    int spriteWidth = square->GetSize().x;
	    int spriteHeight = square->GetSize().y;

	    square->SetPosition(
		(screenWidth*0.5) + (spriteWidth*col) + colIncrement, 
		(screenHeight/8) + spriteHeight*row + rowIncrement);    

	    square->OnStay = [this, square](std::shared_ptr<GameObject> cursorCrossObj){

		if (mCurrentPlayer.type == PlayerType::PLAYER_TYPE_HUMAN){
		    for (int row = 0; row < 3; row++){
			for (int col = 0; col < 3; col++){
			    if (square->GetGameObjectID() == mGameData.board[row][col]->cellID && mGameData.board[row][col]->available){
				GetGameObject<Sprite>("piece_preview")->SetVisibleState(true);
				GetGameObject<Sprite>("piece_preview")->SetPosition(square->GetPosition().x, square->GetPosition().y);
			    }
			}
		    }
		}
	    };

	    square->OnClick = [this, square](){

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

		auto cell = getCell(square->GetGameObjectID());

		if (cell != nullptr && cell->available){

		    std::cout << "New cross" << std::endl;

		    GetGameObject<Sprite>("piece_preview")->SetVisibleState(false);

		    cell->symbol = mCurrentPlayer.symbol;
		    cell->available = false;

		    std::string key = "cross" + std::to_string(square->GetGameObjectID());
		    auto piece = Create<Sprite>(key, 
						RequestTexture(AssetID::ASSET_TEXTURE_CROSS),
						SDL_Point(200, 200),
						SDL_Point(0, 0),
						static_cast<int>(Layers::SYMBOLS),
					        255);

		    piece->SetTextureSize(200, 200);
		    piece->SetPosition(square->GetPosition().x, square->GetPosition().y);
		    piece->SetCollisionState(false);

		    mCurrentPlayer = mAdversary; 
		}
	    };

	    square->OnExit = [this, square](std::shared_ptr<GameObject> cursorCrossObj){
		GetGameObject<Sprite>("piece_preview")->SetVisibleState(false);
	    };


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
    mAIController = std::make_unique<AIController>(
	GenerateTerminalFunction(),
	GenerateEvaluateStateFunction(mAdversary.symbol, mPlayer.symbol),
	GenerateSuccessionFunction(mAdversary.symbol, mPlayer.symbol));

    // Create sprite pieces
    auto piecePreview = Create<Sprite>("piece_preview", 
				       RequestTexture(AssetID::ASSET_TEXTURE_CROSS), 
				       SDL_Point(200, 200), 
				       SDL_Point(0, 0), 
				       static_cast<int>(Layers::EFFECT), 
				       70);
    
    piecePreview->SetTextureSize(200, 200);
    piecePreview->SetVisibleState(false);
    piecePreview->SetCollisionState(false);

    // Initialize grid
    GenerateGrid(20, 20);


    auto cursor = Create<Sprite>("cursor", 
				 RequestTexture(AssetID::ASSET_TEXTURE_CURSOR),
				 SDL_Point(20, 20),
				 SDL_Point(0, 0),
				 static_cast<int>(Layers::CURSOR),
				 255);

    cursor->SetTextureSize(40, 40);
    cursor->SetQueryOnly(true);
}

void GameScene::Input(){

    auto function = [&](SDL_Event event){

	if (event.type == SDL_EVENT_QUIT){
	    RequestGameStateChange(GameState::GAME_STATE_STOPPED);
	}

	if (event.type == SDL_EVENT_MOUSE_MOTION){
	    mousePosition.x = event.motion.x;
	    mousePosition.y = event.motion.y;
	}

	if (mCurrentPlayer.type == PlayerType::PLAYER_TYPE_HUMAN){
	    if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN){

		auto collidingObj = GetGameObject<Sprite>("cursor")->GetCollidingGameObject();

		if (collidingObj != nullptr) {
		    if ( collidingObj->OnClick != nullptr ) {
			collidingObj->OnClick();	
		    }
		}
	    }
	}
    };

    RequestInput(function);
}

void GameScene::Update(){

    FlushPendingGameObjects();

    GetGameObject<Sprite>("cursor")->SetPosition(mousePosition.x, mousePosition.y);

    if (mCurrentPlayer.type == PlayerType::PLAYER_TYPE_AI){

	auto function = [&](){

	    std::pair<int, int> coordinates = mAIController->GetBestMove(mGameData.board, true);
	    std::cout << coordinates.first << " " << coordinates.second << std::endl;

	    if (coordinates.first != -1 && coordinates.second != -1){

		auto square = GetGameObject<Sprite>(mGameData.board[coordinates.first][coordinates.second]->cellID);

		std::string key = "circle" + std::to_string(square->GetGameObjectID()); 
		auto adversaryPiece = Create<Sprite>(key,
						      RequestTexture(AssetID::ASSET_TEXTURE_CIRCLE),
						      SDL_Point(200, 200),
						      SDL_Point(0, 0),
						      static_cast<int>(Layers::SYMBOLS),
						      255);

		adversaryPiece->SetCollisionState(false);
		adversaryPiece->SetTextureSize(200, 200);


		adversaryPiece->SetPosition(square->GetPosition().x, square->GetPosition().y);

		mGameData.board[coordinates.first][coordinates.second]->available = false;
		mGameData.board[coordinates.first][coordinates.second]->symbol = mCurrentPlayer.symbol;

	    }

	    mCurrentPlayer = mPlayer;
	};

	mTimer.StartTimer(2000, function);
    }

    std::vector<std::shared_ptr<GameObject>> collidables;
    for (auto& [key, value] : GetGameObjects<Sprite>()){
	if (value->GetCollisionState()){
	    collidables.push_back(value);
	}
    }

    RequestCheckCollisions(collidables);

    if (GetTicTacToeWinner(mGameData.board) != ' '){
	RequestSceneChange(SceneType::SCENE_GAME);
    }
}

void GameScene::Render(){

    auto function = [&](){
	
	for (int layer = 0; layer < static_cast<int>(Layers::COUNT); layer++){
	    for (const auto& [key, value] : GetGameObjects<Sprite>()){
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
    ClearGameObjects();
}
 
