#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <functional>
#include <vector>

#include "Utils.h"

char GetTicTacToeWinner(Board board);

bool HasMoves(Board board);

// return IsTerminal
std::function<bool(State)> GenerateTerminalFunction();

// return Evaluate
std::function<int(State, int)> GenerateEvaluateStateFunction(char maximizerSymbol, char minimizerSymbol);

// return Successor
std::function<std::vector<State>(State, bool)> GenerateSuccessionFunction(char playerSymbol, char enemySymbol);

#endif
