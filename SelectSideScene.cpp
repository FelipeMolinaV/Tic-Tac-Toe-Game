#include "SelectSideScene.h"

#include <iostream>
#include <string>

constexpr int SCREEN_PADDING = 10;
constexpr int PIECE_W_PERCENTAGE = 50;
constexpr int PIECE_H_PERCENTAGE = 70;
constexpr int PIECE_PADDING = 50;
constexpr int NOT_SELECTED_ALPHA = 180;
constexpr int MAX_ALPHA = 255;
constexpr int TEXT_W_PERCENTAGE = 100;
constexpr int TEXT_H_PERCENTAGE = 30;
constexpr SDL_Point DEFAULT_POS = {0, 0};
constexpr SDL_Point PIECE_SIZE = {400, 400};
constexpr SDL_Point CURSOR_SIZE = {20, 20};
constexpr SDL_Point TEXT_SIZE = {700, 100};
constexpr SDL_Color COLOR_WHITE = {255, 255, 255, 255};


enum class SelectSideScene::Layers{
    BACKGROUND,
    PIECES,
    TEXT,
    CURSOR,
    COUNT
};


void SelectSideScene::OnEnter(){
    std::cout << "On enter select side scene" << '\n';

    // Create Layouts
    mScreenLayout = std::make_unique<RectLayout>(SCREEN_WIDTH,
						 SCREEN_HEIGHT,
						 SCREEN_ORIGIN_X,
						 SCREEN_ORIGIN_Y,
						 SCREEN_PADDING,
						 SCREEN_PADDING);

    mCrossLayout = std::make_unique<RectLayout>(mScreenLayout->CreateRectLayout(PIECE_W_PERCENTAGE,
										PIECE_H_PERCENTAGE,
										TOP,
										LEFT,
										PIECE_PADDING,
										PIECE_PADDING));

    mCircleLayout = std::make_unique<RectLayout>(mScreenLayout->CreateRectLayout(PIECE_W_PERCENTAGE,
										 PIECE_H_PERCENTAGE,
										 TOP,
										 RIGHT,
										 PIECE_PADDING,
										 PIECE_PADDING));

    mTextLayout = std::make_unique<RectLayout>(mScreenLayout->CreateRectLayout(TEXT_W_PERCENTAGE,
									       TEXT_H_PERCENTAGE,
									       BOTTOM,
									       LEFT));

    // Create sprites
    
    auto background = Create<Sprite>("background",
				     RequestTexture(AssetID::ASSET_TEXTURE_GREEN_RED_BACKGROUND),
				     SCREEN_SIZE,
				     DEFAULT_POS,
				     static_cast<int>(Layers::BACKGROUND),
				     MAX_ALPHA);

    background->SetCollisionState(false);

    auto cursor = Create<Sprite>("cursor1", 
				 RequestTexture(AssetID::ASSET_TEXTURE_CURSOR),
				 CURSOR_SIZE,
				 DEFAULT_POS,
				 static_cast<int>(Layers::CURSOR),
				 MAX_ALPHA);

    cursor->SetTextureSize(CURSOR_SIZE.x*2, CURSOR_SIZE.y*2);
    cursor->SetQueryOnly(true);

    auto cross = Create<Sprite>("cross",
				RequestTexture(AssetID::ASSET_TEXTURE_CROSS),
				PIECE_SIZE,
				mCrossLayout->GetMiddleRight(PIECE_SIZE),
				static_cast<int>(Layers::PIECES),
				NOT_SELECTED_ALPHA);

    cross->OnStay = [=](std::shared_ptr<GameObject> obj){
	cross->SetAlpha(MAX_ALPHA); 
    };

    cross->OnExit = [=](std::shared_ptr<GameObject> obj){
	cross->SetAlpha(NOT_SELECTED_ALPHA);
    };

    cross->OnClick = [=](){

	int cursorId = GetGameObject<Sprite>("cursor1")->GetGameObjectID();	

	if (cross->HasCollision(cursorId)){
	    std::cout << "Cross on click" << std::endl;

	    GameData gameData;
	    gameData.playerA.symbol = 'X';
	    gameData.playerA.type = PlayerType::PLAYER_TYPE_HUMAN;
	    gameData.playerB.symbol = 'O';
	    gameData.playerB.type = PlayerType::PLAYER_TYPE_AI;
	    mSceneDataTransfer->SendData(gameData);
	}
    };

    auto circle = Create<Sprite>("circle",
				RequestTexture(AssetID::ASSET_TEXTURE_CIRCLE),
				PIECE_SIZE,
				mCircleLayout->GetMiddleLeft(PIECE_SIZE),
				static_cast<int>(Layers::PIECES),
				NOT_SELECTED_ALPHA);

    circle->OnStay = [=](std::shared_ptr<GameObject> obj){
	circle->SetAlpha(MAX_ALPHA); 
    };

    circle->OnExit = [=](std::shared_ptr<GameObject> obj){
	circle->SetAlpha(NOT_SELECTED_ALPHA);
    };

    circle->OnClick = [=](){

	int cursorId = GetGameObject<Sprite>("cursor1")->GetGameObjectID();	

	if (circle->HasCollision(cursorId)){
	    std::cout << "Circle on click" << std::endl;

	    GameData gameData;
	    gameData.playerA.symbol = 'O';
	    gameData.playerA.type = PlayerType::PLAYER_TYPE_HUMAN;
	    gameData.playerB.symbol = 'X';
	    gameData.playerB.type = PlayerType::PLAYER_TYPE_AI;
	    mSceneDataTransfer->SendData(gameData);
	}
    };

    // Create texts
    
    std::string t = "First to 10 points wins";
    auto text = Create<Text>("text",
			     RequestFontAtlas(AssetID::ASSET_FONT_ATLAS_GABATO_WHITE_124),
			     t,
			     COLOR_WHITE,
			     TEXT_SIZE,
			     mTextLayout->GetMiddleCenter(TEXT_SIZE),
			     static_cast<int>(Layers::TEXT),
			     MAX_ALPHA);

    text->SetCollisionState(false);
}
void SelectSideScene::Input(){

    auto input = [&](SDL_Event event){

	if (event.type == SDL_EVENT_QUIT){
	    RequestGameStateChange(GameState::GAME_STATE_STOPPED);
	}

	if (event.type == SDL_EVENT_MOUSE_MOTION){
	    mMousePosition.x = event.motion.x;
	    mMousePosition.y = event.motion.y;
	}

	if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN){

	    auto cursor = GetGameObject<Sprite>("cursor1");

	    auto collidingObj = cursor->GetCollidingGameObject();

	    if (collidingObj != nullptr) {
		if ( collidingObj->OnClick != nullptr ) {

		    collidingObj->OnClick();	

		    RequestSceneChange(SceneType::SCENE_GAME);

		}
	    }
	}
    };

    RequestInput(input);
}
void SelectSideScene::Update(){

    FlushPendingGameObjects();

    GetGameObject<Sprite>("cursor1")->SetPosition(mMousePosition.x, mMousePosition.y);

    RequestCheckCollisions(GetCollidableObjects());
}

void SelectSideScene::Render(){

    auto render = [&](){

	auto renderableObjects = GetRenderableObjects();

	for (int layer = 0; layer < static_cast<int>(Layers::COUNT); layer++){
	    for (auto& obj : renderableObjects){
		if (obj->GetLayer() == layer){
		    obj->Render();
		}
	    }
	}
    };

    RequestRender(render);
}
void SelectSideScene::OnExit(){ 
    std::cout << "On exit select side scene" << '\n';
    
    ClearData();
}
