#include "TestScene.h"
#include "GameState.h"

#include <iostream>
#include <utility>

void TestScene::OnEnter(){
    std::cout << "On enter Test scene" << '\n';

    // RectLayout::RectLayout(int width, int height, int x, int y){
    mScreenLayout = std::make_unique<RectLayout>(SCREEN_WIDTH, SCREEN_HEIGHT, ORIGEN_X, ORIGEN_Y, PADDING_X, PADDING_Y); 
    mLeftColumn = std::make_unique<RectLayout>(mScreenLayout->CreateRectLayout(20, 100, TOP, LEFT));
    mRightColumn = std::make_unique<RectLayout>(mScreenLayout->CreateRectLayout(20, 100, TOP, RIGHT));
    mCenterColumn = std::make_unique<RectLayout>(mScreenLayout->CreateRectLayout(60, 100, TOP, CENTER, 5, 5));
}

void TestScene::Input(){

    auto input = [&](SDL_Event event){

	if (event.type == SDL_EVENT_QUIT){
	    RequestGameStateChange(GameState::GAME_STATE_STOPPED);
	}

	if (event.type == SDL_EVENT_KEY_DOWN){
	    if (event.key.key == SDLK_C){

		SDL_Point s = {0, 0};

		std::cout << "----- SCREEN RECT LAYOUT -------" << std::endl;
		std::cout << "W: " << mScreenLayout->GetWidth() << std::endl;
		std::cout << "H: " << mScreenLayout->GetHeight() << std::endl;
		std::cout << "TOP-LEFT: " << mScreenLayout->GetTopLeft(s).x << ", " << mScreenLayout->GetTopLeft(s).y << "\n"; 
		std::cout << "TOP-CENTER: " << mScreenLayout->GetTopCenter(s).x << ", " << mScreenLayout->GetTopCenter(s).y << "\n"; 
		std::cout << "TOP-RIGHT: " << mScreenLayout->GetTopRight(s).x << ", " << mScreenLayout->GetTopRight(s).y << "\n"; 
		std::cout << "MIDDLE-LEFT: " << mScreenLayout->GetMiddleLeft(s).x << ", " << mScreenLayout->GetMiddleLeft(s).y << "\n"; 
		std::cout << "MIDDLE-CENTER: " << mScreenLayout->GetMiddleCenter(s).x << ", " << mScreenLayout->GetMiddleCenter(s).y << "\n"; 
		std::cout << "MIDDLE-RIGHT: " << mScreenLayout->GetMiddleRight(s).x << ", " << mScreenLayout->GetMiddleRight(s).y << "\n"; 
		std::cout << "BOTTOM-LEFT: " << mScreenLayout->GetBottomLeft(s).x << ", " << mScreenLayout->GetBottomLeft(s).y << "\n"; 
		std::cout << "BOTTOM-CENTER: " << mScreenLayout->GetBottomCenter(s).x << ", " << mScreenLayout->GetBottomCenter(s).y << "\n"; 
		std::cout << "BOTTOM-RIGHT: " << mScreenLayout->GetBottomRight(s).x << ", " << mScreenLayout->GetBottomRight(s).y << "\n"; 

		std::cout << "-------- LEFT COLUMN RECT LAYOUT ------- " << std::endl;
		std::cout << "W: " << mLeftColumn->GetWidth() << std::endl;
		std::cout << "H: " << mLeftColumn->GetHeight() << std::endl;
		std::cout << "TOP-LEFT: " << mLeftColumn->GetTopLeft(s).x << ", " << mLeftColumn->GetTopLeft(s).y << "\n"; 
		std::cout << "TOP-CENTER: " << mLeftColumn->GetTopCenter(s).x << ", " << mLeftColumn->GetTopCenter(s).y << "\n"; 
		std::cout << "TOP-RIGHT: " << mLeftColumn->GetTopRight(s).x << ", " << mLeftColumn->GetTopRight(s).y << "\n"; 
		std::cout << "MIDDLE-LEFT: " << mLeftColumn->GetMiddleLeft(s).x << ", " << mLeftColumn->GetMiddleLeft(s).y << "\n"; 
		std::cout << "MIDDLE-CENTER: " << mLeftColumn->GetMiddleCenter(s).x << ", " << mLeftColumn->GetMiddleCenter(s).y << "\n"; 
		std::cout << "MIDDLE-RIGHT: " << mLeftColumn->GetMiddleRight(s).x << ", " << mLeftColumn->GetMiddleRight(s).y << "\n"; 
		std::cout << "BOTTOM-LEFT: " << mLeftColumn->GetBottomLeft(s).x << ", " << mLeftColumn->GetBottomLeft(s).y << "\n"; 
		std::cout << "BOTTOM-CENTER: " << mLeftColumn->GetBottomCenter(s).x << ", " << mLeftColumn->GetBottomCenter(s).y << "\n"; 
		std::cout << "BOTTOM-RIGHT: " << mLeftColumn->GetBottomRight(s).x << ", " << mLeftColumn->GetBottomRight(s).y << "\n"; 

		std::cout << "-------- RIGHT COLUMN RECT LAYOUT ------- " << std::endl;
		std::cout << "W: " << mRightColumn->GetWidth() << std::endl;
		std::cout << "H: " << mRightColumn->GetHeight() << std::endl;
		std::cout << "TOP-LEFT: " << mRightColumn->GetTopLeft(s).x << ", " << mRightColumn->GetTopLeft(s).y << "\n"; 
		std::cout << "TOP-CENTER: " << mRightColumn->GetTopCenter(s).x << ", " << mRightColumn->GetTopCenter(s).y << "\n"; 
		std::cout << "TOP-RIGHT: " << mRightColumn->GetTopRight(s).x << ", " << mRightColumn->GetTopRight(s).y << "\n"; 
		std::cout << "MIDDLE-LEFT: " << mRightColumn->GetMiddleLeft(s).x << ", " << mRightColumn->GetMiddleLeft(s).y << "\n"; 
		std::cout << "MIDDLE-CENTER: " << mRightColumn->GetMiddleCenter(s).x << ", " << mRightColumn->GetMiddleCenter(s).y << "\n"; 
		std::cout << "MIDDLE-RIGHT: " << mRightColumn->GetMiddleRight(s).x << ", " << mRightColumn->GetMiddleRight(s).y << "\n"; 
		std::cout << "BOTTOM-LEFT: " << mRightColumn->GetBottomLeft(s).x << ", " << mRightColumn->GetBottomLeft(s).y << "\n"; 
		std::cout << "BOTTOM-CENTER: " << mRightColumn->GetBottomCenter(s).x << ", " << mRightColumn->GetBottomCenter(s).y << "\n"; 
		std::cout << "BOTTOM-RIGHT: " << mRightColumn->GetBottomRight(s).x << ", " << mRightColumn->GetBottomRight(s).y << "\n"; 
	    }
	}
    };

    RequestInput(input);
}

void TestScene::Update(){}

void TestScene::Render(){

    auto render = [&](){

	SDL_Point obj = {0, 0};
	SDL_FRect leftColumnRect = {(float) mLeftColumn->GetTopLeft(obj).x, 
				    (float) mLeftColumn->GetTopLeft(obj).y,
				    (float) mLeftColumn->GetWidth(),
				    (float) mLeftColumn->GetHeight()};

	SDL_FRect rightColumnRect = {(float) mRightColumn->GetTopLeft(obj).x, 
				    (float) mRightColumn->GetTopLeft(obj).y,
				    (float) mRightColumn->GetWidth(),
				    (float) mRightColumn->GetHeight()};

	SDL_FRect centerColumnRect = {(float) mCenterColumn->GetTopLeft(obj).x, 
				    (float) mCenterColumn->GetTopLeft(obj).y,
				    (float) mCenterColumn->GetWidth(),
				    (float) mCenterColumn->GetHeight()};


	SDL_FRect screenRect = {(float) mScreenLayout->GetTopLeft(obj).x, 
				    (float) mScreenLayout->GetTopLeft(obj).y,
				    (float) mScreenLayout->GetWidth(),
				    (float) mScreenLayout->GetHeight()};
	
	SDL_SetRenderDrawColor(mGame->GetRenderer(), 10, 89, 30, 255);
	SDL_RenderRect(mGame->GetRenderer(), &centerColumnRect);	
	SDL_SetRenderDrawColor(mGame->GetRenderer(), 0, 255, 0, 255);
	SDL_RenderRect(mGame->GetRenderer(), &screenRect);	
	SDL_SetRenderDrawColor(mGame->GetRenderer(), 255, 0, 0, 255);
	SDL_RenderRect(mGame->GetRenderer(), &leftColumnRect);	
	SDL_SetRenderDrawColor(mGame->GetRenderer(), 0, 0, 255, 255);
	SDL_RenderRect(mGame->GetRenderer(), &rightColumnRect);	

	SDL_Point s = {100, 100};
	SDL_Point coord = mLeftColumn->GetTopCenter(s);
	SDL_FRect box1 = {(float) coord.x,
			  (float) coord.y,
			  (float) s.x,
	                  (float) s.y};

	SDL_SetRenderDrawColor(mGame->GetRenderer(), 66, 65, 12, 255);
	SDL_RenderRect(mGame->GetRenderer(), &box1);	
	
	s = {200, 400};
	coord = mLeftColumn->GetMiddleLeft(s);
	box1 = {(float) coord.x,
			  (float) coord.y,
			  (float) s.x,
	                  (float) s.y};

	SDL_SetRenderDrawColor(mGame->GetRenderer(), 66, 65, 12, 255);
	SDL_RenderRect(mGame->GetRenderer(), &box1);	
    };

    RequestRender(render);
}

void TestScene::OnExit(){}
