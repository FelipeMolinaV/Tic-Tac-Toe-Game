#ifndef AICONTROLLER_H
#define AICONTROLLER_H

#include <functional>
#include <utility>

#include "Utils.h"

class AIController{

public:

    AIController(std::function<bool(State)> IsTerminal,
		 std::function<int(State, int)> Evaluate,
		 std::function<std::vector<State>(State, bool)> Successors);

    std::pair<int, int> GetBestMove(State state);
    std::pair<int, int> GetBestMove(Board board);
    std::pair<int, int> GetBestMove(Board borad, bool isAlphaBetaPrunning);

private:

    int Minimax(State state, int depth, bool isMaximizing);
    int MinimaxAlphaBetaPrunning(State state, int depth, int alpha, int beta, bool isMaximizing);

    std::function<bool(State)> mIsTerminal;
    std::function<int(State, int)> mEvaluate;
    std::function<std::vector<State>(State, bool)> mSuccessors;
};

#endif
