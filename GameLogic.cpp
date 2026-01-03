#include "GameLogic.h"


char GetTicTacToeWinner(Board board, char playerSymbol, char enemySymbol){

    char winner = ' ';

    for (int row = 0; row < 3; row++){

	int col = 0;
	if (board[row][col].available) continue;
	char auxSymbol = board[row][col].symbol;
	if (auxSymbol != playerSymbol && auxSymbol != enemySymbol) continue;

	for (col = 1; col < 3 && board[row][col].symbol == auxSymbol; col++);

	if (col >= 3){
	    winner = auxSymbol;
	}
    }

    // Vertical line check
    for (int col = 0; col < 3; col++){

	int row = 0;
	if (board[row][col].available) continue;
	char auxSymbol = board[row][col].symbol;
	if (auxSymbol != playerSymbol && auxSymbol != enemySymbol) continue;

	for (row = 1; row < 3 && board[row][col].symbol == auxSymbol; row++);

	if (row >= 3){
	    winner = auxSymbol;
	}
	
    }

    // Diagonal top left to bottom rigth 
    int row = 0;
    int col = 0;
    if (!board[row][col].available){
	char auxSymbol = board[row][col].symbol;
	if (!(auxSymbol != playerSymbol && auxSymbol != enemySymbol)){
	    for (row = 1, col = 1; row < 3 && board[row][col].symbol == auxSymbol; row++, col++);  

	    if (row >= 3){
		winner = auxSymbol;
	    }
	}
    }

    // Diagonal top left to bottom left
    row = 0;
    col = 2;
    if (!board[row][col].available){
	char auxSymbol = board[row][col].symbol;
	if (!(auxSymbol != playerSymbol && auxSymbol != enemySymbol)){
	    for (row = 1, col = 1; row < 3 && board[row][col].symbol == auxSymbol; row++, col--);  

	    if (row >= 3){
		winner = auxSymbol;
	    }
	}
    }

    return winner;
}

std::function<bool(State)> GenerateTerminalFunction(char playerSymbol, char enemySymbol){
    
    auto function = [&](State state){

	if (!(GetTicTacToeWinner(state.board, playerSymbol, enemySymbol) != ' ')){
	    return false;
	}

	for (int row = 0; row < 3; row++){
	    for (int col = 0; col < 3; col++){
		if (state.board[row][col].available) return false;
	    }
	}

	return true;
    };

    return function;
}

std::function<int(State)> GenerateEvaluateStateFunction(char maximizerSymbol, char minimizerSymbol){


    auto function = [&](State state){

	char winner = GetTicTacToeWinner(state.board, maximizerSymbol, minimizerSymbol);

	if (winner == ' '){
	    return 0;
	}
	else if (winner == maximizerSymbol){
	    return 1;
	}
	else {
	    return -1;
	}
    };

    return function;
}

std::function<std::vector<State>(State)> GenerateSuccessionFunction(char playerSymbol, char enemySymbol){

    auto function = [&](State state){

	std::vector<State> states;

	for (int row = 0; row < 3; row++){
	    for (int col = 0; col < 3; col++){

		if (state.board[row][col].available){

		    State newState;
		    newState.board = state.board;
		    newState.board[row][col].symbol = state.currentPlayerSymbol;
		    newState.board[row][col].available = false;

		    if (state.currentPlayerSymbol == playerSymbol){
			newState.currentPlayerSymbol = enemySymbol;
		    }
		    else if (state.currentPlayerSymbol == enemySymbol){
			newState.currentPlayerSymbol = playerSymbol;
		    }

		    states.push_back(newState);
		}
	    }
	}

	return states;
    };

    return function;

}

