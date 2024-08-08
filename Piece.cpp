#include "Piece.h"
#include "raymath.h"

bool Piece::isValidMove()
{
    Vector2 myMove{}; //compute myMove
    for(auto it: this->allowedmoves)
        if(Vector2Equals(it, myMove))
            return true;
    return false;
}

Piece::~Piece()
{
    UnloadTexture(sprite);
    allowedmoves.clear();
}
