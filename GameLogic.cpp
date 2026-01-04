#include "GameLogic.h"
#include <iostream>


char GetTicTacToeWinner(Board board){

    char winner = ' ';

    for (int row = 0; row < 3; row++){

	int col = 0;

	if (board[row][col]->available) continue;
	char auxSymbol = board[row][col]->symbol;

	for (col = 1; col < 3 && board[row][col]->symbol == auxSymbol; col++);

	if (col >= 3){
	    winner = auxSymbol;
	}
    }

    // Vertical line check
    for (int col = 0; col < 3; col++){

	int row = 0;
	if (board[row][col]->available) continue;
	char auxSymbol = board[row][col]->symbol;

	for (row = 1; row < 3 && board[row][col]->symbol == auxSymbol; row++);

	if (row >= 3){
	    winner = auxSymbol;
	}
	
    }

    // Diagonal top left to bottom rigth 
    int row = 0;
    int col = 0;
    if (!board[row][col]->available){
	char auxSymbol = board[row][col]->symbol;
	for (row = 1, col = 1; row < 3 && board[row][col]->symbol == auxSymbol; row++, col++);  

	if (row >= 3){
	    winner = auxSymbol;
	}
    }

    // Diagonal top right to bottom left
    row = 0;
    col = 2;
    if (!board[row][col]->available){
	char auxSymbol = board[row][col]->symbol;
	for (row = 1, col = 1; row < 3 && board[row][col]->symbol == auxSymbol; row++, col--);  

	if (row >= 3){
	    winner = auxSymbol;
	}
    }

    return winner;
}

std::function<bool(State)> GenerateTerminalFunction(){
    
    auto function = [=](State state){

	if (GetTicTacToeWinner(state.board) != ' '){
	    return true;
	}

	for (int row = 0; row < 3; row++){
	    for (int col = 0; col < 3; col++){
		if (state.board[row][col]->available) return false;
	    }
	}

	return true;
    };

    return function;
}

std::function<int(State, int)> GenerateEvaluateStateFunction(char maximizerSymbol, char minimizerSymbol){


    auto function = [=](State state, int penalizer){

	char winner = GetTicTacToeWinner(state.board);

	if (winner == ' ') return 0;

	if (winner == maximizerSymbol){
	    return 100 - penalizer;
	}
	else {
	    return -100 + penalizer;
	}
    };

    return function;
}

std::function<std::vector<State>(State, bool)> GenerateSuccessionFunction(char maximizerSymbol, char minimizerSymbol){

    auto function = [=](State state, bool isMaximizing){

	std::vector<State> states;

	for (int row = 0; row < 3; row++){
	    for (int col = 0; col < 3; col++){

		if (state.board[row][col]->available){

		    State newState = state;

		    newState.board[row][col]->symbol = (isMaximizing == true) ? maximizerSymbol : minimizerSymbol;
		    newState.board[row][col]->available = false;

		    states.push_back(newState);
		}
	    }
	}

	return states;
    };

    return function;

}

