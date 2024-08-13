#ifndef CHESSSET_H
#define CHESSSET_H

#include <vector>
#include "Types.h"
#include "Piece.h"
#include "King.h"
#include "Queen.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Pawn.h"

class ChessSet
{
public:
    ChessSet(PLAYER_COLORS color);
    void draw() const;
    Piece * findPieceByPosition(Vector2 place) const;
    King * getKing() const { return (King*)this->pieces.at(0); }; 
    ~ChessSet();
private:
    std::vector<Piece*> pieces;
};

#endif