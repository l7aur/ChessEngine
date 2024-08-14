#include "Queen.h"

Queen::Queen(Vector2 pos, bool color)
{
    this->position = pos;
    for(int i = 1; i < 8; i++) {
        this->allowedMoves.push_back({static_cast<float>(i), static_cast<float>(i)});
        this->allowedMoves.push_back({static_cast<float>(i), static_cast<float>(-i)});
        this->allowedMoves.push_back({static_cast<float>(-i), static_cast<float>(-i)});
        this->allowedMoves.push_back({static_cast<float>(-i), static_cast<float>(i)});

        this->allowedMoves.push_back({0, static_cast<float>(i)});
        this->allowedMoves.push_back({0, static_cast<float>(-i)});
        this->allowedMoves.push_back({static_cast<float>(i), 0});
        this->allowedMoves.push_back({static_cast<float>(-i), 0});
    }
    this->attackMoves = this->allowedMoves;
    sprite = (color == WHITE_PLAYER) ? LoadTexture("Sprites\\white_queen.png") : LoadTexture("Sprites\\black_queen.png");
}

Queen::~Queen()
{
    UnloadTexture(this->sprite);
}
