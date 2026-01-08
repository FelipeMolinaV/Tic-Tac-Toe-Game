#include "AIController.h"

#include <algorithm>
#include <iostream>
#include <cmath>

AIController::AIController(std::function<bool(State)> isTerminal,
			   std::function<int(State, int)> evaluate,
			   std::function<std::vector<State>(State, bool)> successors)
{
    mIsTerminal = isTerminal;
    mEvaluate = evaluate;
    mSuccessors = successors;
};

int AIController::Minimax(State state, int depth, bool isMaximizing){

    if (mIsTerminal(state)){
	return mEvaluate(state, depth);
    }

    if (isMaximizing){
	int bestValue = -1000;
	for (auto& s : mSuccessors(state, isMaximizing)){
	    int value = Minimax(s, depth + 1, !isMaximizing);	
	    bestValue = std::max(bestValue, value);
	}
	return bestValue;
    }
    else {
	int bestValue = 1000;
	for (auto& s : mSuccessors(state, isMaximizing)){
	    int value = Minimax(s, depth + 1, !isMaximizing);	
	    bestValue = std::min(bestValue, value);
	}
	return bestValue;
    }
}

int AIController::MinimaxAlphaBetaPrunning(State state, int depth, int alpha, int beta, bool isMaximizing){

    if (mIsTerminal(state)){
	return mEvaluate(state, depth);
    }

    if (isMaximizing){
	int bestValue = -1000;
	for (auto& s : mSuccessors(state, isMaximizing)){

	    int value = MinimaxAlphaBetaPrunning(s, depth + 1, alpha, beta, !isMaximizing);	
	    bestValue = std::max(bestValue, value);
	    alpha =  std::max(bestValue, alpha);

	    if (beta <= alpha){
		break;
	    }
	}
	return bestValue;
    }
    else {
	int bestValue = 1000;
	for (auto& s : mSuccessors(state, isMaximizing)){
	    int value = MinimaxAlphaBetaPrunning(s, depth + 1, alpha, beta, !isMaximizing);	
	    bestValue = std::min(bestValue, value);
	    beta = std::min(bestValue, beta);

	    if (beta <= alpha){
		break;
	    }
	}
	return bestValue;
    }
}

std::pair<int, int> AIController::GetBestMove(State state){

    State bestMove;
    int bestValue = -1000;

    for (auto s : mSuccessors(state, true)){
	int value = Minimax(s, 0, false);
	if (value > bestValue){
	    bestValue = value;
	    bestMove = s;
	}
    }

    for (int row = 0; row < 3; row++){
	for (int col = 0; col < 3; col++){
	    if (state.board[row][col]->symbol == bestMove.board[row][col]->symbol) continue;
	    return {row, col};
	}
    }

    return {-1, -1};
}

std::pair<int, int> AIController::GetBestMove(Board board){

    State state;
    state.board = board;

    State bestMove;
    int bestValue = -1000;

    for (auto s : mSuccessors(state, true)){
	int value = Minimax(s, 0, false);
	if (value > bestValue){
	    bestValue = value;
	    bestMove = s;
	}
    }


    for (int row = 0; row < 3; row++){
	for (int col = 0; col < 3; col++){
	    if (state.board[row][col]->symbol == bestMove.board[row][col]->symbol) continue;
	    return {row, col};
	}
    }

    return {-1, -1};
}

std::pair<int, int> AIController::GetBestMove(Board board, bool isAlphaBetaPrunning){

    State state;
    state.board = board;

    bool boardFull = true;

    for (int row = 0; row < 3; row++){
	for (int col = 0; col < 3; col++){
	    if (state.board[row][col]->available){
		boardFull = false;
		break;
	    }
	}
    }

    if (boardFull) return {-1, -1};

    State bestMove;
    int bestValue = -1000;

    for (auto s : mSuccessors(state, true)){
	int value = (isAlphaBetaPrunning) ? 
	    MinimaxAlphaBetaPrunning(s, 0, -1000, 1000, false) :
	    Minimax(s, 0, false);
	if (value > bestValue){
	    bestValue = value;
	    bestMove = s;
	}
    }


    for (int row = 0; row < 3; row++){
	for (int col = 0; col < 3; col++){
	    if (state.board[row][col]->symbol == bestMove.board[row][col]->symbol) continue;
	    return {row, col};
	}
    }

    return {-1, -1};
}

