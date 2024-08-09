#include "ChessSet.h"
#include "raymath.h"

ChessSet::ChessSet(PLAYER_COLORS color)
{
    int line = (color == WHITE_PLAYER) ? 7 : 0;
    int reflect = (color == WHITE_PLAYER) ? -1 : 1;
    this->pieces.push_back(new King({3, static_cast<float>(line)}, color));
    this->pieces.push_back(new Queen({4, static_cast<float>(line)}, color));
    this->pieces.push_back(new Rook({0, static_cast<float>(line)}, color));
    this->pieces.push_back(new Rook({7, static_cast<float>(line)}, color));
    this->pieces.push_back(new Knight({1, static_cast<float>(line)}, color));
    this->pieces.push_back(new Knight({6, static_cast<float>(line)}, color));
    this->pieces.push_back(new Bishop({2, static_cast<float>(line)}, color));
    this->pieces.push_back(new Bishop({5, static_cast<float>(line)}, color));
    for (int i = 0; i < 8; i++)
        this->pieces.push_back(new Pawn({static_cast<float>(i), static_cast<float>(reflect + line),}, color));

    
}

void ChessSet::draw() const
{
    for(Piece* p: this->pieces)
        if(p->toBeDrawn)
            p->draw(p->computeBoardPosition());
}

Piece *ChessSet::findPieceByPosition(Vector2 place) const
{
    for(Piece* p: this->pieces)
        if(Vector2Equals(p->getPosition(), place))
            return p;
    return nullptr;
}

ChessSet::~ChessSet()
{
    for(Piece* p: this->pieces)
        delete p;
    this->pieces.clear();
}
