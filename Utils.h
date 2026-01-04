#ifndef UTILS_H
#define UTILS_H

#include <memory>
#include <array>
#include <utility>

struct Cell{
    char symbol = ' ';
    int cellID = -1;
    bool available = true;
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
};

struct GameData{

    Board board;

    GameData(){
	for (int row = 0; row < 3; row++){
	    for (int col = 0; col < 3; col++){
		board[row][col] = std::make_shared<Cell>();
	    }
	}
    }
};

#endif
