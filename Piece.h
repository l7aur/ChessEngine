#ifndef PIECE_H
#define PIECE_H

#include "raylib.h"
#include <vector>

class Piece
{
public:
    bool isInsideBoard(); //todo
    bool isValidMove(); //todo
    ~Piece();
protected:
    Texture2D sprite{};
    Vector2 position{};
    std::vector <Vector2> allowedmoves{};
    bool color{};
};

#endif