#include "Knight.h"

Knight::Knight(Vector2 pos, bool color)
{
    this->position = pos;
    this->allowedmoves.push_back({2, 1});
    this->allowedmoves.push_back({2, -1});
    this->allowedmoves.push_back({-2, 1});
    this->allowedmoves.push_back({-2, -1});
    this->allowedmoves.push_back({1, 2});
    this->allowedmoves.push_back({1, -2});
    this->allowedmoves.push_back({-1, 2});
    this->allowedmoves.push_back({-1, -2});
    // sprite = (color == WHITE_PLAYER) ? LoadTexture() : LoadTexture();
}