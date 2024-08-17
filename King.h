#ifndef KING_H
#define KING_H

#include "Piece.h"

class King : public Piece
{
public:
    King(Vector2 pos, bool color);
    inline bool getCanCastle() const { return this->canCastle; };
    inline bool getInCheck() const { return this->inCheck; };
    inline void unsetCanCastle() { this->canCastle = false; };
    inline void setInCheck(bool state) { this->inCheck = state; };
    ~King();

private:
    bool canCastle{true};
    bool inCheck{false};
};

#endif