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
    void draw();
    ~Piece();
protected:
    Texture2D sprite{};
    Vector2 position{};
    std::vector<Vector2> allowedmoves{};
    bool color{};
private:
    Rectangle computeBordPosition();
};

#endif