#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include "Types.h"
#include "raylib.h"

class ChessBoard
{
public:
    ChessBoard(float size);
    void drawChessBoard(Color firstColor, Color secondColor) const;
    bool isInside(Vector2 v) const;
    BoardPlace at(int i, int j) const;
private:
    BoardPlace board[8][8];
};

#endif