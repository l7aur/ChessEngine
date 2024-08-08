#include "Knight.h"

Knight::Knight(Vector2 pos, bool color)
{
    this->position = pos;
    this->allowedmoves.push_back({2, -1});
    this->allowedmoves.push_back({-2, 1});
    this->allowedmoves.push_back({-2, -1});
    this->allowedmoves.push_back({1, 2});
    this->allowedmoves.push_back({1, -2});
    this->allowedmoves.push_back({-1, 2});
    this->allowedmoves.push_back({-1, -2});
    // sprite = (color == WHITE_PLAYER) ? LoadTexture("Sprites\\white_knight.png") : LoadTexture("Sprites\\black_knight.png");
    sprite = LoadTexture("Sprites\\white_knight.png");
}

void Knight::draw(BoardPlace place)
{
    Rectangle spriteRec{0, 0, static_cast<float>(this->sprite.width), static_cast<float>(this->sprite.height)};
    DrawTexturePro(this->sprite, spriteRec, place.position, {}, 0.0f, WHITE);
}
