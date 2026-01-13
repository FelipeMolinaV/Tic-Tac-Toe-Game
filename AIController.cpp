#include "AIController.h"

#include <algorithm>
#include <iostream>

AIController::AIController(std::function<bool(State)> isTerminal,
			   std::function<int(State, int)> evaluate,
			   std::function<std::vector<State>(State, bool)> successors)
    : gen(std::random_device{}())   
{
    mIsTerminal = isTerminal;
    mEvaluate = evaluate;
    mSuccessors = successors;
    mIsThinking = false; 
    mIsRequestPending = false;

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

std::pair<int, int> AIController::GetBestMove(Board board, int winProbability, bool isAlphaBetaPrunning){

    std::uniform_int_distribution<> dis(0, 100);

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

    State worstMove;
    int worstValue = 1000;

    for (auto s : mSuccessors(state, true)){
	int value = (isAlphaBetaPrunning) ? 
	    MinimaxAlphaBetaPrunning(s, 0, -1000, 1000, false) :
	    Minimax(s, 0, false);
	if (value > bestValue){
	    bestValue = value;
	    bestMove = s;
	}

	if (value < worstValue){
	    worstValue = value;
	    worstMove = s;
	}
    }

    int successProb = dis(gen);

    State nextState = (successProb > winProbability) ? worstMove : bestMove;

    for (int row = 0; row < 3; row++){
	for (int col = 0; col < 3; col++){
	    if (state.board[row][col]->symbol == nextState.board[row][col]->symbol) continue;
	    return {row, col};
	}
    }

    return {-1, -1};
}

void AIController::RequestBestMove(Board board, int winProbability){
    mIsThinking = true;
    mIsRequestPending = true;
    mBestMoveCoordinates = std::async(std::launch::async, [this, board, winProbability](){
	return GetBestMove(board, winProbability, true);
    });
}

bool AIController::IsRequestPending(){
    return mIsRequestPending;
}

bool AIController::IsThinking(){

    if (!mIsThinking) return false;
    
    if (mBestMoveCoordinates.wait_for(std::chrono::seconds(0)) == std::future_status::ready){
	return false;
    }

    return true;
}

std::pair<int, int> AIController::GetResult(){
    mIsThinking = false;
    mIsRequestPending = false;
    return mBestMoveCoordinates.get();
}
