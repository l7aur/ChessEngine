#ifndef PIECE_H
#define PIECE_H

#include "raylib.h"
#include "Types.h"
#include <vector>
#include <algorithm>

class Piece
{
public:
    bool isInsideBoard(); // todo
    bool isValidMove();   // todo
    void draw(Rectangle boardPosition);
    Rectangle computeBoardPosition();
    Rectangle computeBoardPosition(Vector2 mouse, Vector2 board);
    inline Vector2 getPosition() { return this->position; };
    inline void setPosition(Vector2 newPos) { this->position = newPos; };
    ~Piece();
    bool toBeDrawn{true};
protected:
    Texture2D sprite{};
    Vector2 position{};
    std::vector<Vector2> allowedmoves{};
    bool color{};
private:
};

#endif