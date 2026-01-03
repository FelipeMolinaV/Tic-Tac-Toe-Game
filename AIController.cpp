#include "AIController.h"

#include <algorithm>

AIController::AIController(std::function<bool(State)> isTerminal,
			   std::function<int(State)> evaluate,
			   std::function<std::vector<State>(State)> successors)
{
    mIsTerminal = isTerminal;
    mEvaluate = evaluate;
    mSuccessors = successors;
};

int AIController::Minimax(State state, bool isMaximizing){

    if (mIsTerminal(state)){
	return mEvaluate(state);
    }

    if (isMaximizing){
	int bestValue = -1000;
	for (auto& s : mSuccessors(state)){
	   bestValue = std::max(bestValue, Minimax(s, false));
	}
	return bestValue;
    }
    else {
	int bestValue = 1000;
	for (auto& s : mSuccessors(state)){
	    bestValue = std::min(bestValue, Minimax(s, true));
	}
	return bestValue;
    }
}

std::pair<int, int> AIController::GetBestMove(const State& state){

    State bestMove;
    int bestValue = -1000;

    for (auto& s : mSuccessors(state)){
	int value = Minimax(state, true);
	if (value >= bestValue){
	    bestValue = value;
	    bestMove = s;
	}
    }

    for (int row = 0; row < 3; row++){
	for (int col = 0; col < 3; col++){
	    if (state.board[row][col].symbol == bestMove.board[row][col].symbol) continue;
	    return {row, col};
	}
    }
}


