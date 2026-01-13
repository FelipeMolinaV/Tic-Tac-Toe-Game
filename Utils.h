#ifndef UTILS_H
#define UTILS_H

#include <SDL3/SDL.h>

#include <memory>
#include <array>
#include <utility>

constexpr int SCREEN_WIDTH = 1280;
constexpr int SCREEN_HEIGHT = 720;
constexpr int SCREEN_ORIGIN_X = 0;
constexpr int SCREEN_ORIGIN_Y = 0;
constexpr SDL_Point SCREEN_CENTER = {SCREEN_WIDTH/2, SCREEN_HEIGHT/2};
constexpr SDL_Point SCREEN_SIZE = {SCREEN_WIDTH, SCREEN_HEIGHT};

struct Cell{
    char symbol = ' ';
    int cellID = -1;
    bool available = true;
    int row = -1;
    int col = -1;
};

using Board = std::array<std::array<std::shared_ptr<Cell>, 3>, 3>;

struct State{

    Board board;

    // TODO: Move this implementation to cpp

    State(){
	for (int row = 0; row < 3; row++){
	    for (int col = 0; col < 3; col++){
		board[row][col] = std::make_shared<Cell>();
	    }
	}
    };

    // Copy Constructor
    State(const State& other){
	for (int row = 0; row < 3; row++){
	    for (int col = 0; col < 3; col++){
		board[row][col] = std::make_shared<Cell>();
		board[row][col]->symbol = other.board[row][col]->symbol;
		board[row][col]->cellID = other.board[row][col]->cellID;
		board[row][col]->available = other.board[row][col]->available;
		
	    }
	}
    }

    // Copy assignment operator
    State& operator=(const State& other){
	if (this != &other){
	    for (int row = 0; row < 3; row++){
		for (int col = 0; col < 3; col++){
		    board[row][col] = std::make_shared<Cell>();
		    board[row][col]->symbol = other.board[row][col]->symbol;
		    board[row][col]->cellID = other.board[row][col]->cellID;
		    board[row][col]->available = other.board[row][col]->available;
		}
	    }
	}
	return *this;
    }

    
};

enum class PlayerType {
    PLAYER_TYPE_HUMAN,
    PLAYER_TYPE_AI
};

struct PlayerData {
    char symbol;
    PlayerType type;
    int wins = 0;
};

struct GameData{

    Board board;
    PlayerData playerA;
    PlayerData playerB;
    PlayerData winner;

    GameData(){
	int i = 1;
	for (int row = 0; row < 3; row++){
	    for (int col = 0; col < 3; col++){
		board[row][col] = std::make_shared<Cell>();
		board[row][col]->cellID = i++;
		board[row][col]->row = row;
		board[row][col]->col = col;
	    }
	}
    };

    void ResetBoard(){
	for (int row = 0; row < 3; row++){
	    for (int col = 0; col < 3; col++){
		board[row][col]->symbol = ' ';
		board[row][col]->available = true;
	    }
	}
    };

    std::shared_ptr<Cell> GetCellByID(int cellId){
	for (int row = 0; row < 3; row++){
	    for (int col = 0; col < 3; col++){
		if (board[row][col]->cellID == cellId) return board[row][col]; 
	    }
	}
	return nullptr;
    };
};

#endif
