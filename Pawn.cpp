#include "Pawn.h"
#include "Types.h"

Pawn::Pawn(Vector2 pos, bool color)
{
    this->id = PIECE::PAWN;
    position = pos;
    if(!this->isInsideBoard())
        throw std::invalid_argument("\nPAWN\nReceived wrong value for position!\n");
    if (color == WHITE_PLAYER)
    {
        sprite = LoadTexture("Sprites\\white_pawn.png");
        this->moves.push_back({0, -1});
        this->moves.push_back({1, -1});
        this->moves.push_back({-1, -1});
        this->specialMoves.push_back({0, -2});
    }
    else
    {
        sprite = LoadTexture("Sprites\\black_pawn.png");
        this->moves.push_back({0, 1});
        this->moves.push_back({1, 1});
        this->moves.push_back({-1, 1});
        this->specialMoves.push_back({0, 2});
    }
}