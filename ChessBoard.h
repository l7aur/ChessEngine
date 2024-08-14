#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

#include "Miscellaneous.h"
#include "ChessSet.h"
#include "raylib.h"
#include <utility>
#include <iomanip>
#include <iostream>
#include <string>

class ChessBoard
{
public:
    ChessBoard(float size);
    void draw(Color firstColor, Color secondColor) const;
    bool isInside(int i, int j) const;
    inline ChessSet *getWhiteSet() const { return this->whiteSet; };
    inline ChessSet *getBlackSet() const { return this->blackSet; };
    inline BoardPlace (*getAbstractBoard())[8] { return this->board; };
    void updatePosition(Vector2 oldPos, Vector2 newPos);
    BoardPlace at(int i, int j) const;
    void printState() const;
    ~ChessBoard();

private:
    void setBoardIds();
    BoardPlace board[8][8];
    ChessSet *whiteSet, *blackSet;
};
#endif