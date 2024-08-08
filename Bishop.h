#ifndef BISHOP_H
#define BISHOP_H

#include "Piece.h"

class Bishop : public Piece
{
public:
    Bishop(Vector2 pos, bool color);
    ~Bishop() { Piece::~Piece(); };
private:
};

#endif