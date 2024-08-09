#include "Piece.h"
#include "raymath.h"

bool Piece::isInsideBoard() const
{
    if (position.x < 0 || position.x > 7)
        return false;
    if (position.y < 0 || position.y > 7)
        return false;
    return true;
}

void Piece::draw(Rectangle placePosition) const
{
    Rectangle spriteRec{0, 0, static_cast<float>(this->sprite.width), static_cast<float>(this->sprite.height)};
    DrawTexturePro(this->sprite, spriteRec, placePosition, {}, 0.0f, WHITE);
}

Piece::~Piece()
{
    UnloadTexture(sprite);
    moves.clear();
}

Rectangle Piece::computeBoardPosition() const
{
    Rectangle r{};
    r.y = this->position.y * SQUARE_SIZE + PADDING;
    r.x = this->position.x * SQUARE_SIZE + PADDING;
    r.width = r.height = SQUARE_SIZE - 2 * PADDING;
    return r;
}

Rectangle Piece::computeBoardPosition(Vector2 mouse, Vector2 board) const
{
    Rectangle r{};
    Vector2 boardVect = Vector2Scale(board, SQUARE_SIZE);
    Vector2 displacement = Vector2Subtract(mouse, boardVect);
    r.y = mouse.y - displacement.y + PADDING;
    r.x = mouse.x - displacement.x + PADDING;
    r.height = r.width = SQUARE_SIZE - 2 * PADDING;
    return r;
}
