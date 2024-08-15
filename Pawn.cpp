#include "Pawn.h"

Pawn::Pawn(Vector2 pos, bool color)
{
    this->position = pos;
    if (color == WHITE_PLAYER)
    {
        sprite = LoadTexture("Sprites\\white_pawn.png");
        this->allowedMoves.push_back({-1, 0});
        this->attackMoves.push_back({-1, 1});
        this->attackMoves.push_back({-1, -1});
        this->specialMoves.push_back({-2, 0});
    }
    else
    {
        sprite = LoadTexture("Sprites\\black_pawn.png");
        this->allowedMoves.push_back({1, 0});
        this->attackMoves.push_back({1, 1});
        this->attackMoves.push_back({1, -1});
        this->specialMoves.push_back({2, 0});
    }
    this->extremityMoves = this->allowedMoves;
    for(auto i: attackMoves)
        this->extremityMoves.push_back(i);

}

Pawn::~Pawn()
{
    UnloadTexture(this->sprite);
}
