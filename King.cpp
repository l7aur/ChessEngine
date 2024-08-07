#include "King.h"

King::King(Vector2 pos, bool color)
{
    this->position = pos;
    this->allowedmoves.push_back({0, 1});
    this->allowedmoves.push_back({0, -1});
    this->allowedmoves.push_back({1, 1});
    this->allowedmoves.push_back({1, -1});
    this->allowedmoves.push_back({1, 0});
    this->allowedmoves.push_back({-1, 0});
    this->allowedmoves.push_back({-1, 1});
    this->allowedmoves.push_back({-1, -1});
    // sprite = (color == WHITE_PLAYER) ? LoadTexture() : LoadTexture();
}