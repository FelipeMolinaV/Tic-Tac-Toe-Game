#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <functional>
#include <vector>

#include "Utils.h"

char GetTicTacToeWinner(Board board, char playerSymbol, char enemySymbol);

// return IsTerminal
std::function<bool(State)> GenerateTerminalFunction(char playerSymbol, char enemySymbol);

// return Evaluate
std::function<int(State)> GenerateEvaluateStateFunction(char maximizerSymbol, char minimizerSymbol);

// return Successor
std::function<std::vector<State>(State)> GenerateSuccessionFunction(char playerSymbol, char enemySymbol);

#endif
