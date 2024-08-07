#include "Piece.h"
#include <algorithm>

bool Piece::isValidMove()
{
    Vector2 myMove{}; //compute myMove
    if(std::find(allowedmoves.begin(), allowedmoves.end(), myMove) == allowedmoves.end())
        return false;
    return true;
}

Piece::~Piece()
{
    UnloadTexture(sprite);
    allowedmoves.clear();
}
