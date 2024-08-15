#include "Rook.h"
#include "raymath.h"

Rook::Rook(Vector2 pos, bool color)
{
    position = pos;
    this->allowedMoves.push_back({1, 0});
    this->allowedMoves.push_back({0, 1});
    this->allowedMoves.push_back({-1, 0});
    this->allowedMoves.push_back({0, -1});
    for(auto i: this->allowedMoves) 
        this->extremityMoves.push_back(Vector2Scale(i, 10));
    this->attackMoves = this->allowedMoves;
    sprite = (color == WHITE_PLAYER) ? LoadTexture("Sprites\\white_rook.png") : LoadTexture("Sprites\\black_rook.png");
}

Rook::~Rook()
{
    UnloadTexture(this->sprite);
}
