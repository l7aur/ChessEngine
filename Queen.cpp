#include "Queen.h"
#include "raymath.h"

Queen::Queen(Vector2 pos, bool color)
{
    this->position = pos;
    this->allowedMoves.push_back({1, 1});
    this->allowedMoves.push_back({1, -1});
    this->allowedMoves.push_back({-1, 1});
    this->allowedMoves.push_back({-1, -1});
    this->allowedMoves.push_back({1, 0});
    this->allowedMoves.push_back({0, 1});
    this->allowedMoves.push_back({-1, 0});
    this->allowedMoves.push_back({0, -1});
    for(auto i: this->allowedMoves)
        this->extremityMoves.push_back(Vector2Scale(i, 10));
    this->attackMoves = this->allowedMoves;
    sprite = (color == WHITE_PLAYER) ? LoadTexture("Sprites\\white_queen.png") : LoadTexture("Sprites\\black_queen.png");
}

Queen::~Queen()
{
    UnloadTexture(this->sprite);
}
