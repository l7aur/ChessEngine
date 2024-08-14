#include "King.h"
#include "raymath.h"
#include <iostream>

King::King(Vector2 pos, bool color)
{
    this->position = pos;
    this->allowedMoves.push_back({0, 1});
    this->allowedMoves.push_back({0, -1});
    this->allowedMoves.push_back({1, 1});
    this->allowedMoves.push_back({1, -1});
    this->allowedMoves.push_back({1, 0});
    this->allowedMoves.push_back({-1, 0});
    this->allowedMoves.push_back({-1, 1});
    this->allowedMoves.push_back({-1, -1});
    this->specialMoves.push_back({2, 0});
    this->specialMoves.push_back({-2, 0});
    this->attackMoves = this->allowedMoves;
    sprite = (color == WHITE_PLAYER) ? LoadTexture("Sprites\\white_king.png") : LoadTexture("Sprites\\black_king.png");
}

King::~King()
{
    UnloadTexture(this->sprite);
}
