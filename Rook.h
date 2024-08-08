#ifndef ROOK_H
#define ROOK_H

#include "Piece.h"

class Rook : public Piece {
public:
    Rook(Vector2 pos, bool color);
    ~Rook() { Piece::~Piece(); };
};

#endif