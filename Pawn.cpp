#include "Pawn.h"

Pawn::Pawn(Vector2 pos, bool color)
{
    this->position = pos;
    if (color == WHITE_PLAYER)
    {
        sprite = LoadTexture("Sprites\\white_pawn.png");
        this->allowedMoves.push_back({0, -1});
        this->attackMoves.push_back({1, -1});
        this->attackMoves.push_back({-1, -1});
        this->specialMoves.push_back({0, -1});
        this->specialMoves.push_back({0, -2});
    }
    else
    {
        sprite = LoadTexture("Sprites\\black_pawn.png");
        this->allowedMoves.push_back({0, 1});
        this->attackMoves.push_back({1, 1});
        this->attackMoves.push_back({-1, 1});
        this->specialMoves.push_back({0, 1});
        this->specialMoves.push_back({0, 2});
    }
}

Pawn::~Pawn()
{
    UnloadTexture(this->sprite);
}
