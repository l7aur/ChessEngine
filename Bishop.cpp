#include "Bishop.h"

Bishop::Bishop(Vector2 pos, bool color)
{
    this->position = pos;
    for(int i = 1; i < 8; i++) {
        this->allowedmoves.push_back({static_cast<float>(i), static_cast<float>(i)});
        this->allowedmoves.push_back({static_cast<float>(i), static_cast<float>(-i)});
        this->allowedmoves.push_back({static_cast<float>(-i), static_cast<float>(i)});
        this->allowedmoves.push_back({static_cast<float>(-i), static_cast<float>(-i)});
    }

    // sprite = (color == WHITE_PLAYER) ? LoadTexture() : LoadTexture();
}