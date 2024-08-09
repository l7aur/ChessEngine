#include "Piece.h"
#include "raymath.h"

bool Piece::isInsideBoard()
{
    if(position.x < 0 || position.x > 7)
        return false;
    if(position.y < 0 || position.y > 7)
        return false;
    return true;
}

bool Piece::isValidMove()
{
    Vector2 myMove{}; //compute myMove
    for(auto it: this->allowedmoves)
        if(Vector2Equals(it, myMove))
            return true;
    return false;
}

void Piece::draw(Rectangle placePosition)
{
    Rectangle spriteRec{0, 0, static_cast<float>(this->sprite.width), static_cast<float>(this->sprite.height)};
    DrawTexturePro(this->sprite, spriteRec, placePosition, {}, 0.0f, WHITE);
}

Piece::~Piece()
{
    UnloadTexture(sprite);
    allowedmoves.clear();
}

Rectangle Piece::computeBoardPosition()
{
    Rectangle r{};
    r.x = this->position.y * SQUARE_SIZE + PADDING;
    r.y = this->position.x * SQUARE_SIZE + PADDING;
    r.width = r.height = SQUARE_SIZE - 2 * PADDING;
    return r;
}

Rectangle Piece::computeBoardPosition(Vector2 mouse, Vector2 board)
{
    Rectangle r{};
    Vector2 boardVect = Vector2Scale(board, 100);
    Vector2 displacement = Vector2Subtract(mouse, boardVect);
    r.y = mouse.x - displacement.x + PADDING;
    r.x = mouse.y - displacement.y + PADDING;
    r.height = r.width = SQUARE_SIZE - 2 * PADDING;
    return r;
}
