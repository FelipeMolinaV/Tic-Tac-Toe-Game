#ifndef UTILS_H
#define UTILS_H

#include <array>

struct Cell{
    char symbol = ' ';
    bool available = true;
};

using Board = std::array<std::array<Cell, 3>, 3>;

struct State{
    Board board;
    char currentPlayerSymbol;
};

#endif
