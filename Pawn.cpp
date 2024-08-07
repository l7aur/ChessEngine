#include "Pawn.h"
#include "Types.h"

Pawn::Pawn(Vector2 pos, bool color)
{
    position = pos;
    if (color == WHITE_PLAYER)
    {
        // sprite = LoadTexture();
        this->allowedmoves.push_back({0, -1});
        this->allowedmoves.push_back({1, -1});
        this->allowedmoves.push_back({-1, -1});
    }
    else
    {
        // sprite = LoadTexture();
        this->allowedmoves.push_back({0, 1});
        this->allowedmoves.push_back({1, 1});
        this->allowedmoves.push_back({-1, 1});
    }
}