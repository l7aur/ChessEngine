#include "Rook.h"
#include "Types.h"

Rook::Rook(Vector2 pos, bool color)
{
    position = pos;
    if(!this->isInsideBoard())
        throw std::invalid_argument("\nROOK\nreceived wrong value for position!\n");
    for (int i = 1; i < 8; i++)
        this->allowedmoves.push_back({0, -static_cast<float>(i)});
    for (int i = 1; i < 8; i++)
        this->allowedmoves.push_back({0, static_cast<float>(i)});
    for (int i = 1; i < 8; i++)
        this->allowedmoves.push_back({-static_cast<float>(i), 0});
    for (int i = 1; i < 8; i++)
        this->allowedmoves.push_back({static_cast<float>(i), 0});
    sprite = (color == WHITE_PLAYER) ? LoadTexture("Sprites\\white_rook.png") : LoadTexture("Sprites\\black_rook.png");
}