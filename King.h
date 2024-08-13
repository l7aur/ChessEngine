#ifndef KING_H
#define KING_H

#include "Piece.h"

class King: public Piece {
public:
    King(Vector2 pos, bool color);
    ~King() { Piece::~Piece(); };
    // bool hihglightCheck(ChessSet * set) const;
private:
};

#endif