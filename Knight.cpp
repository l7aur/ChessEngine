#include "Knight.h"
#include <iostream>
Knight::Knight(Vector2 pos, bool color)
{
    this->position = pos;
    this->allowedMoves.push_back({2, -1});
    this->allowedMoves.push_back({-2, 1});
    this->allowedMoves.push_back({-2, -1});
    this->allowedMoves.push_back({2, 1});
    this->allowedMoves.push_back({1, 2});
    this->allowedMoves.push_back({1, -2});
    this->allowedMoves.push_back({-1, 2});
    this->allowedMoves.push_back({-1, -2});
    this->attackMoves = this->allowedMoves;
    sprite = (color == WHITE_PLAYER) ? LoadTexture("Sprites\\white_knight.png") : LoadTexture("Sprites\\black_knight.png");
}

Knight::~Knight()
{
    UnloadTexture(this->sprite);
}
