#include "Bishop.h"

Bishop::Bishop(Vector2 pos, bool color)
{
    this->position = pos;
    if (!this->isInsideBoard())
        throw std::invalid_argument("\nBISHOP\nReceived wrong value for position!\n");
    for (int i = 1; i < 8; i++)
    {
        this->moves.push_back({static_cast<float>(i), static_cast<float>(i)});
        this->moves.push_back({static_cast<float>(i), static_cast<float>(-i)});
        this->moves.push_back({static_cast<float>(-i), static_cast<float>(i)});
        this->moves.push_back({static_cast<float>(-i), static_cast<float>(-i)});
    }
    this->attackMoves = this->moves;
    sprite = (color == WHITE_PLAYER) ? LoadTexture("Sprites\\white_bishop.png") : LoadTexture("Sprites\\black_bishop.png");
}