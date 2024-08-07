#ifndef PIECE_H
#define PIECE_H

#include "raylib.h"
#include <vector>

class Piece
{
public:
protected:
    Vector2 position{};
    std::vector <Vector2> allowedmoves{};
    bool color{};
};

#endif