#ifndef PIECE_H
#define PIECE_H

#include "raylib.h"
#include "Types.h"
#include "ChessBoard.h"
#include <vector>
#include <algorithm>

class Piece
{
public:
    bool isInsideBoard() const;
    void draw(Rectangle boardPosition) const;
    Rectangle computeBoardPosition() const;
    Rectangle computeBoardPosition(Vector2 mouse, Vector2 board) const;
    inline Vector2 getPosition() const { return this->position; };
    inline void setPosition(Vector2 newPos) { this->position = newPos; };
    inline Vector2 getPreviousPosition() const { return this->previousPosition; };
    inline void updatePreviousPosition() { this->previousPosition = position; };
    void highlightAllowedMoves(ChessBoard *board) const;
    ~Piece();

    bool toBeDrawn{true};

protected:
    Texture2D sprite{};
    Vector2 previousPosition{};
    Vector2 position{};
    std::vector<Vector2> allowedmoves{};
    bool color{};

private:
};

#endif