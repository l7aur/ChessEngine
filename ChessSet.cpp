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
}

void ChessSet::draw() const
{
    king->draw(king->getPixelPosition());
    queen->draw(queen->getPixelPosition());
    rook[0]->draw(rook[0]->getPixelPosition()), rook[1]->draw(rook[1]->getPixelPosition());
    knight[0]->draw(knight[0]->getPixelPosition()), knight[1]->draw(knight[1]->getPixelPosition());
    bishop[0]->draw(bishop[0]->getPixelPosition()), bishop[1]->draw(bishop[1]->getPixelPosition());
    for (int i = 0; i < 8; i++)
        pawn[i]->draw(pawn[i]->getPixelPosition());
}

std::vector<Piece *> ChessSet::getPieces() const
{
    std::vector<Piece *> v;
    v.push_back(king);
    v.push_back(queen);
    v.push_back(rook[0]), v.push_back(rook[1]);
    v.push_back(knight[0]), v.push_back(knight[1]);
    v.push_back(bishop[0]), v.push_back(bishop[1]);
    for (int i = 0; i < 8; i++)
        v.push_back(pawn[i]);
    return v;
}

Piece *ChessSet::getPieceByPosition(Vector2 position) const
{
    std::vector<Piece*> myPieces = this->getPieces();
    for(auto p: myPieces)
        if(Vector2Equals(p->getPosition(), position))
            return p;
    return nullptr;
}

ChessSet::~ChessSet()
{
    delete this->king;
    delete this->queen;
    delete this->rook[0], delete this->rook[1];
    delete this->knight[0], delete this->knight[1];
    delete this->bishop[0], delete this->bishop[1];
    for (int i = 0; i < 8; i++)
        delete pawn[i];
}
