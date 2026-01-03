#ifndef AICONTROLLER_H
#define AICONTROLLER_H

#include <functional>
#include <utility>

#include "Utils.h"

class AIController{

public:

    AIController(std::function<bool(State)> IsTerminal,
		 std::function<int(State)> Evaluate,
		 std::function<std::vector<State>(State)> Successors);

    std::pair<int, int> GetBestMove(const State& state);

private:

    int Minimax(State state, bool isMaximizing);

    std::function<bool(State)> mIsTerminal;
    std::function<int(State)> mEvaluate;
    std::function<std::vector<State>(State)> mSuccessors;
};

#endif
