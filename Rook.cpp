#include "Rook.h"

Rook::Rook(Vector2 pos, bool color)
{
    position = pos;
    for (int i = 1; i < 8; i++)
        this->allowedMoves.push_back({0, -static_cast<float>(i)});
    for (int i = 1; i < 8; i++)
        this->allowedMoves.push_back({0, static_cast<float>(i)});
    for (int i = 1; i < 8; i++)
        this->allowedMoves.push_back({-static_cast<float>(i), 0});
    for (int i = 1; i < 8; i++)
        this->allowedMoves.push_back({static_cast<float>(i), 0});
    this->attackMoves = this->allowedMoves;
    sprite = (color == WHITE_PLAYER) ? LoadTexture("Sprites\\white_rook.png") : LoadTexture("Sprites\\black_rook.png");
}

Rook::~Rook()
{
    UnloadTexture(this->sprite);
}
