#include "AIController.h"

#include <algorithm>
#include <iostream>

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


