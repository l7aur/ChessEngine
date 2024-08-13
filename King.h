#ifndef KING_H
#define KING_H

#include "Piece.h"

class King: public Piece {
public:
    King(Vector2 pos, bool color);
    ~King() { Piece::~Piece(); };
    // bool checkForCheck(Piece * piece, std::vector<Vector2> moves) const;
    // void hihglightCheck() const;
private:
};

#endif