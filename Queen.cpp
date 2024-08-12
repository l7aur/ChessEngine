#include "Queen.h"

Queen::Queen(Vector2 pos, bool color)
{
    this->position = pos;
    if(!this->isInsideBoard())
        throw std::invalid_argument("\nQUEEN\nReceived wrong value for position!\n");
    for(int i = 1; i < 8; i++) {
        this->moves.push_back({static_cast<float>(i), static_cast<float>(i)});
        this->moves.push_back({static_cast<float>(i), static_cast<float>(-i)});
        this->moves.push_back({static_cast<float>(-i), static_cast<float>(-i)});
        this->moves.push_back({static_cast<float>(-i), static_cast<float>(i)});

        this->moves.push_back({0, static_cast<float>(i)});
        this->moves.push_back({0, static_cast<float>(-i)});
        this->moves.push_back({static_cast<float>(i), 0});
        this->moves.push_back({static_cast<float>(-i), 0});
    }
    this->attackMoves = this->moves;
    sprite = (color == WHITE_PLAYER) ? LoadTexture("Sprites\\white_queen.png") : LoadTexture("Sprites\\black_queen.png");
}