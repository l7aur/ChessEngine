#ifndef KING_H
#define KING_H

#include "Piece.h"

class King : public Piece
{
public:
    King(Vector2 pos, bool color);
    inline bool getCanCastle() const { return this->canCastle; };
    inline void unsetCanCastle() { this->canCastle = false; };
    ~King();

private:
    bool canCastle{true};
};

#endif