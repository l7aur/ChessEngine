#include "Knight.h"
#include <iostream>
Knight::Knight(Vector2 pos, bool color)
{
    this->position = pos;
    if(!this->isInsideBoard())
        throw std::invalid_argument("received wrong value for position!");
    this->allowedmoves.push_back({2, -1});
    this->allowedmoves.push_back({-2, 1});
    this->allowedmoves.push_back({-2, -1});
    this->allowedmoves.push_back({1, 2});
    this->allowedmoves.push_back({1, -2});
    this->allowedmoves.push_back({-1, 2});
    this->allowedmoves.push_back({-1, -2});
    sprite = (color == WHITE_PLAYER) ? LoadTexture("Sprites\\white_knight.png") : LoadTexture("Sprites\\black_knight.png");
}
