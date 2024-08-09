#include "ChessSet.h"
#include "raymath.h"

ChessSet::ChessSet(PLAYER_COLORS color)
{
    int line = (color == WHITE_PLAYER) ? 7 : 0;
    int reflect = (color == WHITE_PLAYER) ? -1 : 1;
    this->pieces.push_back(new King({static_cast<float>(line), 3}, color));
    this->pieces.push_back(new Queen({static_cast<float>(line), 4}, color));
    this->pieces.push_back(new Rook({static_cast<float>(line), 0}, color));
    this->pieces.push_back(new Rook({static_cast<float>(line), 7}, color));
    this->pieces.push_back(new Knight({static_cast<float>(line), 1}, color));
    this->pieces.push_back(new Knight({static_cast<float>(line), 6}, color));
    this->pieces.push_back(new Bishop({static_cast<float>(line), 2}, color));
    this->pieces.push_back(new Bishop({static_cast<float>(line), 5}, color));
    for (int i = 0; i < 8; i++)
        this->pieces.push_back(new Pawn({static_cast<float>(reflect + line), static_cast<float>(i)}, color));

    
}

void ChessSet::draw()
{
    for(Piece* p: this->pieces)
        if(p->toBeDrawn)
            p->draw(p->computeBoardPosition());
}

Piece *ChessSet::findPieceByPosition(Vector2 place)
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
