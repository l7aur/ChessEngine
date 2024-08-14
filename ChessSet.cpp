#include "ChessSet.h"
#include "raymath.h"

ChessSet::ChessSet(PLAYER_COLORS player)
{
    float firstLine = (player == PLAYER_COLORS::WHITE_PLAYER) ? 7 : 0;
    float secondLine = firstLine + ((player == PLAYER_COLORS::WHITE_PLAYER) ? -1 : 1);
    this->king = new King({firstLine, 3}, player);
    this->queen = new Queen({firstLine, 4}, player);
    this->rook[0] = new Rook({firstLine, 0}, player), this->rook[1] = new Rook({firstLine, 7}, player);
    this->knight[0] = new Knight({firstLine, 1}, player), this->knight[1] = new Knight({firstLine, 6}, player);
    this->bishop[0] = new Bishop({firstLine, 2}, player), this->bishop[1] = new Bishop({firstLine, 5}, player);
    for (int i = 0; i < 8; i++)
        this->pawn[i] = new Pawn({secondLine, static_cast<float>(i)}, player);
    piecesOnBoard.push_back(king);
    piecesOnBoard.push_back(queen);
    piecesOnBoard.push_back(rook[0]), piecesOnBoard.push_back(rook[1]);
    piecesOnBoard.push_back(knight[0]), piecesOnBoard.push_back(knight[1]);
    piecesOnBoard.push_back(bishop[0]), piecesOnBoard.push_back(bishop[1]);
    for (int i = 0; i < 8; i++)
        piecesOnBoard.push_back(pawn[i]);
}

void ChessSet::draw()
{
    for (auto p : this->getPiecesOnBoard())
        p->draw(p->getPixelPosition());
}

Piece *ChessSet::getPieceByPosition(Vector2 position)
{
    std::vector<Piece *> myPieces = this->getPiecesOnBoard();
    for (auto p : myPieces)
        if (Vector2Equals(p->getPosition(), position))
            return p;
    return nullptr;
}

ChessSet::~ChessSet()
{
    this->piecesOnBoard.clear();
    delete this->king;
    delete this->queen;
    delete this->rook[0], delete this->rook[1];
    delete this->knight[0], delete this->knight[1];
    delete this->bishop[0], delete this->bishop[1];
    for (int i = 0; i < 8; i++)
        delete pawn[i];
}
