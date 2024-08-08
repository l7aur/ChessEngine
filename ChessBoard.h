#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include "Types.h"
#include "raylib.h"

class ChessBoard
{
public:
    ChessBoard(float size);
    void drawChessBoard(Color firstColor, Color secondColor);
    BoardPlace at(int i, int j);
private:
    BoardPlace board[8][8];
};

#endif