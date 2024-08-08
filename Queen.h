#ifndef QUEEN_H
#define QUEEN_H

#include "Piece.h"

class Queen : public Piece
{
public:
    Queen(Vector2 pos, bool color);
    ~Queen() { Piece::~Piece(); };
private:
};

#endif