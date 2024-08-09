#include "King.h"

King::King(Vector2 pos, bool color)
{
    this->position = pos;
    if(!this->isInsideBoard())
        throw std::invalid_argument("\nKING\nReceived wrong value for position!\n");
    this->moves.push_back({0, 1});
    this->moves.push_back({0, -1});
    this->moves.push_back({1, 1});
    this->moves.push_back({1, -1});
    this->moves.push_back({1, 0});
    this->moves.push_back({-1, 0});
    this->moves.push_back({-1, 1});
    this->moves.push_back({-1, -1});
    sprite = (color == WHITE_PLAYER) ? LoadTexture("Sprites\\white_king.png") : LoadTexture("Sprites\\black_king.png");
}