#ifndef AICONTROLLER_H
#define AICONTROLLER_H

#include <functional>
#include <utility>
#include <random>
#include <future>

#include "Utils.h"

class AIController{

public:

    AIController(std::function<bool(State)> IsTerminal,
		 std::function<int(State, int)> Evaluate,
		 std::function<std::vector<State>(State, bool)> Successors);

    void RequestBestMove(Board board, int winProbability);
    bool IsThinking();
    bool IsRequestPending();
    std::pair<int, int> GetResult();

private:

    int Minimax(State state, int depth, bool isMaximizing);
    int MinimaxAlphaBetaPrunning(State state, int depth, int alpha, int beta, bool isMaximizing);

    std::function<bool(State)> mIsTerminal;
    std::function<int(State, int)> mEvaluate;
    std::function<std::vector<State>(State, bool)> mSuccessors;

    std::future<std::pair<int, int>> mBestMoveCoordinates;
    bool mIsThinking; 
    bool mIsRequestPending;

    std::mt19937 gen;

    std::pair<int, int> GetBestMove(State state);
    std::pair<int, int> GetBestMove(Board board);
    std::pair<int, int> GetBestMove(Board board, int winProbability, bool isAlphaBetaPrunning);
};

#endif
