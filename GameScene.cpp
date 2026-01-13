#include <iostream>
#include <string>
#include <cmath>
#include <utility>
#include <future>

#include "Asset.h"
#include "Sprite.h"
#include "Text.h"
#include "AudioSource.h"
#include "GameState.h"
#include "AIController.h"
#include "GameScene.h"
#include "Utils.h"

constexpr int ROWS = 3;
constexpr int COLS = 3;
constexpr int SCREEN_PADDING = 10;
constexpr int W_COLUMN_PERCENTAGE = 25;
constexpr int H_COLUMN_PERCENTAGE = 100; 
constexpr int W_CENTER_COLUMN_PERCENTAGE = 50;
constexpr int X_COLUMN_PADDING = 20; 
constexpr int Y_COLUMN_PADDING = 30;
constexpr int MAX_ALPHA = 255;
constexpr int NOT_PLAYING_ALPHA = 70;
constexpr int PIECE_PREVIEW_ALPHA = 100;
constexpr int INVALID_CELL_COORD = -1;
constexpr int MAX_POINTS = 10;
constexpr int INITIAL_CELL_ID = 1;
constexpr int AI_THINKING_TIME = 1000;
constexpr int AI_WIN_PROBABILITY = 65;
constexpr int WAITING_TURN_TIME = 500;
constexpr SDL_Point PLAYERS_TEXT_SIZE = {250, 50};
constexpr SDL_Point PLAYERS_COUNTER_TEXT_SIZE = {200, 400};
constexpr SDL_Point CELL_SIZE = {200, 200};
constexpr SDL_Point PIECE_SIZE = {200, 200};
constexpr SDL_Point CURSOR_SIZE = {20, 20};
constexpr SDL_Point DEFAULT_POS = {0, 0};
constexpr SDL_Color COLOR_BLACK = {0, 0, 0, 255};
constexpr SDL_Color COLOR_WHITE = {255, 255, 255, 255};

enum class GameScene::Layers{
    BACKGROUND,
    UI,
    BOARD,
    EFFECT,
    SYMBOLS,
    CURSOR,
    COUNT
};


// return the coordinates given by the center column Rect Layout depends on the position on the matrix
SDL_Point GetRectLayoutCoordinatesFromMatrix(const std::unique_ptr<RectLayout>& rectLayout, SDL_Point size, int row, int col){

    // First row - Col 1, 2, 3
    if (row == 0 && col == 0) return rectLayout->GetTopLeft(size);
    else if (row == 0 && col == 1) return rectLayout->GetTopCenter(size);
    else if (row == 0 && col == 2) return rectLayout->GetTopRight(size);
    // Second row - Col 1, 2, 3
    else if (row == 1 && col == 0) return rectLayout->GetMiddleLeft(size);
    else if (row == 1 && col == 1) return rectLayout->GetMiddleCenter(size);
    else if (row == 1 && col == 2) return rectLayout->GetMiddleRight(size);
    // Third row - Col 1, 2, 3
    else if (row == 2 && col == 0) return rectLayout->GetBottomLeft(size);
    else if (row == 2 && col == 1) return rectLayout->GetBottomCenter(size);
    else return rectLayout->GetBottomRight(size);
}

void GameScene::GenerateLayouts(){
    
    // Create screen layout with 20 x and y padding
    mScreenLayout = std::make_unique<RectLayout>(SCREEN_WIDTH, 
						 SCREEN_HEIGHT, 
						 SCREEN_ORIGIN_X, 
						 SCREEN_ORIGIN_Y, 
						 SCREEN_PADDING, 
						 SCREEN_PADDING);
    
    mLeftColumnLayout = std::make_unique<RectLayout>(mScreenLayout->CreateRectLayout(W_COLUMN_PERCENTAGE,
										     H_COLUMN_PERCENTAGE,
										     TOP,
										     LEFT,
										     X_COLUMN_PADDING,
										     Y_COLUMN_PADDING));

    mRightColumnLayout = std::make_unique<RectLayout>(mScreenLayout->CreateRectLayout(W_COLUMN_PERCENTAGE,
										      H_COLUMN_PERCENTAGE,
										      TOP,
										      RIGHT,
										      X_COLUMN_PADDING,
										      Y_COLUMN_PADDING));

    // Create center column with 10 x and y padding
    mCenterColumnLayout = std::make_unique<RectLayout>(mScreenLayout->CreateRectLayout(W_CENTER_COLUMN_PERCENTAGE,
										       H_COLUMN_PERCENTAGE,
										       TOP, 
										       CENTER, 
										       0, 
										       Y_COLUMN_PADDING));
}

void GameScene::ConfigureGameData(){

    // Config Players data
    
    mGameData = mSceneDataTransfer->GetData<GameData>();


    // Initialize AIController
    mAIController = std::make_unique<AIController>(
	GenerateTerminalFunction(),
	GenerateEvaluateStateFunction(mGameData.playerB.symbol, mGameData.playerA.symbol),
	GenerateSuccessionFunction(mGameData.playerB.symbol, mGameData.playerA.symbol));

}

void GameScene::UpdatePoints(){

    char winner = GetTicTacToeWinner(mGameData.board); 
    if (winner == mGameData.playerA.symbol){

	mGameData.playerA.wins++;	
	auto playerCounter = GetGameObject<Text>("player_counter");
	playerCounter->SetText(std::to_string(mGameData.playerA.wins));
    }
    else if (winner == mGameData.playerB.symbol){

	mGameData.playerB.wins++;
	auto enemyCounter = GetGameObject<Text>("enemy_counter");
	enemyCounter->SetText(std::to_string(mGameData.playerB.wins));
    }
    
}

void GameScene::HandleGameState(GameData gameData){
    std::cout << "Handle" << std::endl;
    if (gameData.playerA.wins >= MAX_POINTS){
	gameData.winner = gameData.playerA;
	RequestSceneChange(SceneType::SCENE_SELECT_SIDE);
    }
    else if (gameData.playerB.wins >= MAX_POINTS){
	gameData.winner = gameData.playerB;
	RequestSceneChange(SceneType::SCENE_SELECT_SIDE);
    }
    else {

	DeactivatePieces();
	mGameData.ResetBoard();
    }
}

void GameScene::ForEachCell(std::function<void(int, int)> function){
    for (int row = 0; row < ROWS; row++){
	for (int col = 0; col < COLS; col++){
	    function(row, col);
	}
    }
}

void GameScene::SetCurrentPlayer(PlayerData& player){

    mCurrentPlayer = player;

    auto playerText = GetGameObject<Text>("player_text");
    auto enemyText = GetGameObject<Text>("enemy_text");

    if (mCurrentPlayer.type == PlayerType::PLAYER_TYPE_HUMAN){
	playerText->SetAlpha(MAX_ALPHA);
	enemyText->SetAlpha(NOT_PLAYING_ALPHA);
    }
    else {
	enemyText->SetAlpha(MAX_ALPHA);
	playerText->SetAlpha(NOT_PLAYING_ALPHA);
    }
}

void GameScene::CreatePieces(){

    // Create cross and circle sprites in each cell.
    
    // Create cross sprites

    auto crossTexture = RequestTexture(AssetID::ASSET_TEXTURE_CROSS);

    int i = INITIAL_CELL_ID;
    ForEachCell([&](int row, int col){
    
	std::string key = "cross" + std::to_string(i++);
	auto cross = Create<Sprite>(key, 
				    crossTexture,
				    CELL_SIZE,
				    GetRectLayoutCoordinatesFromMatrix(mCenterColumnLayout, CELL_SIZE, row, col),
				    static_cast<int>(Layers::SYMBOLS),
				    MAX_ALPHA);

	cross->SetActive(false);
	cross->SetCollisionState(false);

	mPieces.push_back(cross);
    });

    // Create circle sprites

    auto circleTexture = RequestTexture(AssetID::ASSET_TEXTURE_CIRCLE);

    i = INITIAL_CELL_ID;
    ForEachCell([&](int row, int col){
    
	std::string key = "circle" + std::to_string(i++);
	auto circle = Create<Sprite>(key, 
				    circleTexture,
				    CELL_SIZE,
				    GetRectLayoutCoordinatesFromMatrix(mCenterColumnLayout, CELL_SIZE, row, col),
				    static_cast<int>(Layers::SYMBOLS),
				    MAX_ALPHA);

	circle->SetActive(false);
	circle->SetCollisionState(false);

	mPieces.push_back(circle);
    });
}

void GameScene::DeactivatePieces(){
    for (auto obj : mPieces){
	if (!obj->GetActive()) continue;
	obj->SetActive(false);
    }
}

void GameScene::AddGameObjectToBoard(std::shared_ptr<GameObject> gameObject, std::shared_ptr<Cell> cell){
    mGameObjectOnBoard[gameObject] = cell;
}

std::shared_ptr<Cell> GameScene::GetCellFromGameObject(std::shared_ptr<GameObject> gameObject){
    return mGameObjectOnBoard[gameObject];
}


void GameScene::GenerateBoard(){

    // Create the 9 cell sprites and set their position with the center Rect Layout coordinates
    // update the board game data 
    
    int i = INITIAL_CELL_ID;
    ForEachCell([&](int row, int col){

	// Create Cell sprite and update cell data
	std::string key = "cell" + std::to_string(i);
	auto cellSprite = Create<Sprite>(key, 
					 RequestTexture(AssetID::ASSET_TEXTURE_SQUARE), 
					 CELL_SIZE, 
					 GetRectLayoutCoordinatesFromMatrix(mCenterColumnLayout, CELL_SIZE, row, col),
					 static_cast<int>(Layers::BOARD),
					 MAX_ALPHA);

	AddGameObjectToBoard(cellSprite, mGameData.GetCellByID(i++));

	cellSprite->SetTextureSize(CELL_SIZE.x, CELL_SIZE.y);

	// Define OnStay behaviour to activate the preview piece in a specific cell position when there is colision with the cursor obj
	cellSprite->OnStay = [this, cellSprite](std::shared_ptr<GameObject> cursorCrossObj){

	    if (mCurrentPlayer.type == PlayerType::PLAYER_TYPE_HUMAN){

		auto cell = GetCellFromGameObject(cellSprite);

		if (cell->available){
		    auto piecePreview = GetGameObject<Sprite>("piece_preview");
		    piecePreview->SetVisibleState(true);
		    piecePreview->SetPosition(cellSprite->GetPosition().x, cellSprite->GetPosition().y);
		}
	    }
	};

	// Define OnClick behaviour to create new pieces in a specific cell position
	cellSprite->OnClick = [this, cellSprite](){

	    auto cell = GetCellFromGameObject(cellSprite);

	    if (cell->available){

		GetGameObject<Sprite>("piece_preview")->SetVisibleState(false);

		cell->symbol = mCurrentPlayer.symbol;
		cell->available = false;

		std::string key = (mGameData.playerA.symbol == 'X') ? "cross" + std::to_string(cell->cellID):
								      "circle" + std::to_string(cell->cellID);

		GetGameObject<Sprite>(key)->SetActive(true);

		SetCurrentPlayer(mGameData.playerB);
	    }
	};

	cellSprite->OnExit = [this, cellSprite](std::shared_ptr<GameObject> cursorCrossObj){
	    GetGameObject<Sprite>("piece_preview")->SetVisibleState(false);
	};

    });
}

void GameScene::GenerateSprites(){

    // Crate background
    auto background = Create<Sprite>("background",
				     RequestTexture(AssetID::ASSET_TEXTURE_BACKGROUND),
				     SCREEN_SIZE,
				     DEFAULT_POS,
				     static_cast<int>(Layers::BACKGROUND),
				     MAX_ALPHA);

    background->SetTextureSize(SCREEN_SIZE.x, SCREEN_SIZE.y);
    background->SetCollisionState(false);


    // Create sprite pieces
    auto texture = (mGameData.playerA.symbol == 'X') ? RequestTexture(AssetID::ASSET_TEXTURE_CROSS) : 
						       RequestTexture(AssetID::ASSET_TEXTURE_CIRCLE);

    auto piecePreview = Create<Sprite>("piece_preview", 
				       texture,
				       PIECE_SIZE,
				       DEFAULT_POS,
				       static_cast<int>(Layers::EFFECT), 
				       PIECE_PREVIEW_ALPHA);
    
    piecePreview->SetTextureSize(PIECE_SIZE.x, PIECE_SIZE.y);
    piecePreview->SetVisibleState(false);
    piecePreview->SetCollisionState(false);


    // Create cursor
    auto cursor = Create<Sprite>("cursor", 
				 RequestTexture(AssetID::ASSET_TEXTURE_CURSOR),
				 CURSOR_SIZE,
				 SCREEN_CENTER,
				 static_cast<int>(Layers::CURSOR),
				 MAX_ALPHA);

    cursor->SetTextureSize(CURSOR_SIZE.x*2, CURSOR_SIZE.y*2);
    cursor->SetQueryOnly(true);

    CreatePieces();
}

void GameScene::GenerateTexts(){

    std::string text = "Player"; 
    auto playerText = Create<Text>("player_text",
				   RequestFontAtlas(AssetID::ASSET_FONT_ATLAS_GABATO_WHITE_24),
				   text,
				   COLOR_WHITE,
				   PLAYERS_TEXT_SIZE,
				   mLeftColumnLayout->GetTopCenter(PLAYERS_TEXT_SIZE),
				   static_cast<int>(Layers::UI),
				   MAX_ALPHA);

    playerText->SetCollisionState(false);

    text = "Enemy"; 
    auto enemyText = Create<Text>("enemy_text",
				   RequestFontAtlas(AssetID::ASSET_FONT_ATLAS_GABATO_WHITE_24),
				   text,
				   COLOR_WHITE,
				   PLAYERS_TEXT_SIZE,
				   mRightColumnLayout->GetTopCenter(PLAYERS_TEXT_SIZE),
				   static_cast<int>(Layers::UI),
				   MAX_ALPHA);

    enemyText->SetCollisionState(false);

    // Create wins counts
    std::string counter = "0";
    auto playerCounter = Create<Text>("player_counter",
				      RequestFontAtlas(AssetID::ASSET_FONT_ATLAS_GABATO_WHITE_124),
				      counter,
				      COLOR_WHITE,
				      PLAYERS_COUNTER_TEXT_SIZE,
				      mLeftColumnLayout->GetMiddleCenter(PLAYERS_COUNTER_TEXT_SIZE),
				      static_cast<int>(Layers::UI),
				      MAX_ALPHA);

    playerCounter->SetCollisionState(false);

    auto enemyCounter = Create<Text>("enemy_counter",
				      RequestFontAtlas(AssetID::ASSET_FONT_ATLAS_GABATO_WHITE_124),
				      counter,
				      COLOR_WHITE,
				      PLAYERS_COUNTER_TEXT_SIZE,
				      mRightColumnLayout->GetMiddleCenter(PLAYERS_COUNTER_TEXT_SIZE),
				      static_cast<int>(Layers::UI),
				      MAX_ALPHA);

    enemyCounter->SetCollisionState(false);
}

    
void GameScene::OnEnter(){

    std::cout << "On enter Scene Game" << '\n';

    ConfigureGameData();

    GenerateLayouts();

    GenerateSprites();

    GenerateTexts();

    GenerateBoard();

    FlushPendingGameObjects();

    SetCurrentPlayer(mGameData.playerA);
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

	// TODO: Fix to make easy to call every object that has OnClick and must be called
	if (mCurrentPlayer.type == PlayerType::PLAYER_TYPE_HUMAN){
	    if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN){

		auto cursor = GetGameObject<Sprite>("cursor");

		auto collidingObj = cursor->GetCollidingGameObject();

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

    if (!HasMoves(mGameData.board) || GetTicTacToeWinner(mGameData.board) != ' '){

	auto updateAndReset = [&](){

	    UpdatePoints();

	    // clear pieces if no one has 10 points
	    // End the game if someone has 10 points  
	    HandleGameState(mGameData);
	};

	mTimer.StartTimer(WAITING_TURN_TIME, updateAndReset);
    }

    FlushPendingGameObjects();


    GetGameObject<Sprite>("cursor")->SetPosition(mousePosition.x, mousePosition.y);

    if (mCurrentPlayer.type == PlayerType::PLAYER_TYPE_AI && !mAIController->IsRequestPending()){
	mAIController->RequestBestMove(mGameData.board, AI_WIN_PROBABILITY);
    }

    if (mCurrentPlayer.type == PlayerType::PLAYER_TYPE_AI && !mAIController->IsThinking()){
		
	auto getMove = [&](){

	    std::pair<int, int> coordinates = mAIController->GetResult(); 

	    if (coordinates.first != INVALID_CELL_COORD && coordinates.second != INVALID_CELL_COORD){

		int row = coordinates.first;
		int col = coordinates.second;

		auto cell = mGameData.board[row][col];

		std::string key = (mGameData.playerB.symbol == 'X') ? "cross" + std::to_string(cell->cellID):
								      "circle" + std::to_string(cell->cellID);


		mGameData.board[coordinates.first][coordinates.second]->available = false;
		mGameData.board[coordinates.first][coordinates.second]->symbol = mCurrentPlayer.symbol;

		// Activate piece
		GetGameObject<Sprite>(key)->SetActive(true);

		SetCurrentPlayer(mGameData.playerA);
	    }
	};

	mTimer.StartTimer(AI_THINKING_TIME, getMove);
    }

    RequestCheckCollisions(GetCollidableObjects());
}

void GameScene::Render(){

    auto function = [&](){

	auto renderableObjects = GetRenderableObjects();

	for (int layer = 0; layer < static_cast<int>(Layers::COUNT); layer++){
	    for (auto& obj : renderableObjects){
		if (obj->GetLayer() == layer){
		    obj->Render();
		}
	    }
	}
    };

    RequestRender(function);
}

void GameScene::OnExit(){
    std::cout << "On exit Scene Game" << '\n';
    
    ClearData();
}
 
