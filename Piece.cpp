#include "Piece.h"
#include "raymath.h"
#include <iostream>

Piece::Piece()
{
    this->position = {0.0f, 0.0f};
}

Rectangle Piece::getPixelPosition() const
{
    Rectangle r{};
    r.y = this->position.x * SQUARE_SIZE + PADDING;
    r.x = this->position.y * SQUARE_SIZE + PADDING;
    r.width = r.height = SQUARE_SIZE - 2 * PADDING;
    return r;
}

Rectangle Piece::getPixelPosition(Vector2 mouse, Vector2 board) const
{
    Rectangle r{};
    Vector2 boardVect = Vector2Scale(board, SQUARE_SIZE);
    Vector2 displacement = Vector2Subtract(mouse, boardVect);
    r.x = mouse.y - displacement.y + PADDING;
    r.y = mouse.x - displacement.x + PADDING;
    r.height = r.width = SQUARE_SIZE - 2 * PADDING;
    return r;
}

void Piece::draw(Rectangle place) const
{
    if (this->toBeDrawn)
    {
        Rectangle spriteRec{0, 0, static_cast<float>(this->sprite.width), static_cast<float>(this->sprite.height)};
        DrawTexturePro(this->sprite, spriteRec, place, {}, 0.0f, WHITE);
    }
}
