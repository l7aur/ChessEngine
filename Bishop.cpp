#include "Bishop.h"
#include "raymath.h"

Bishop::Bishop(Vector2 pos, bool color)
{
    this->position = pos;
    this->allowedMoves.push_back({1, 1});
    this->allowedMoves.push_back({1, -1});
    this->allowedMoves.push_back({-1, 1});
    this->allowedMoves.push_back({-1, -1});
    for(auto i: this->allowedMoves)
        this->extremityMoves.push_back(Vector2Scale(i, 10));
    this->attackMoves = this->allowedMoves;
    sprite = (color == WHITE_PLAYER) ? LoadTexture("Sprites\\white_bishop.png") : LoadTexture("Sprites\\black_bishop.png");
}

Bishop::~Bishop()
{
    UnloadTexture(this->sprite);
}
