#include "Bishop.h"

Bishop::Bishop(Vector2 pos, bool color)
{
    this->position = pos;
    for (int i = 1; i < 8; i++)
    {
        this->allowedMoves.push_back({static_cast<float>(i), static_cast<float>(i)});
        this->allowedMoves.push_back({static_cast<float>(i), static_cast<float>(-i)});
        this->allowedMoves.push_back({static_cast<float>(-i), static_cast<float>(i)});
        this->allowedMoves.push_back({static_cast<float>(-i), static_cast<float>(-i)});
    }
    this->attackMoves = this->allowedMoves;
    sprite = (color == WHITE_PLAYER) ? LoadTexture("Sprites\\white_bishop.png") : LoadTexture("Sprites\\black_bishop.png");
}

Bishop::~Bishop()
{
    UnloadTexture(this->sprite);
}
