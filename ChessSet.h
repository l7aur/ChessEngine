#ifndef CHESS_SET_H
#define CHESS_SET_H

#include "Miscellaneous.h"
#include "King.h"
#include "Queen.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Pawn.h"
#include <vector>

class ChessSet
{
public:
    ChessSet(PLAYER_COLORS player);
    void draw() const;
    std::vector<Piece*> getPieces() const;
    Piece * getPieceByPosition(Vector2 position) const;
    ~ChessSet();

private:
    King *king;
    Queen *queen;
    Rook *rook[2];
    Bishop *bishop[2];
    Knight *knight[2];
    Pawn *pawn[8];
};
#endif