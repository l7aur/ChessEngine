#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <algorithm>

#include "ChessBoard.h"
#include "ChessSet.h"
#include "raymath.h"

bool find(std::vector<Vector2> v, Vector2 x)
{
    for (auto i : v)
        if (Vector2Equals(i, x))
            return true;
    return false;
}

std::vector<Vector2> highlightAllowedMoves(ChessBoard *chessBoard, ChessSet *currentSet, ChessSet *opposingSet, Piece *chosenPiece)
{
    std::vector<Vector2> v;
    for (Vector2 allowedM : chosenPiece->getMoves())
    {
        Vector2 boardPos = Vector2Add(chosenPiece->getPosition(), allowedM);
        Vector2 pixelPos = Vector2Scale(boardPos, SQUARE_SIZE);
        Piece *inTargetPos = opposingSet->findPieceByPosition(boardPos);
        if (inTargetPos != nullptr)
        {
            DrawRectangle(pixelPos.x, pixelPos.y, SQUARE_SIZE, SQUARE_SIZE, HIGHLIGHT_AVAILABLE_ATTACK);
            v.push_back(boardPos);
        }
        else
        {
            inTargetPos = currentSet->findPieceByPosition(boardPos);
            if (inTargetPos == nullptr)
            {
                DrawRectangle(pixelPos.x, pixelPos.y, SQUARE_SIZE, SQUARE_SIZE, HIGHLIGHT_AVAILABLE_EMPTY);
                v.push_back(boardPos);
            }
        }
    }
    return v;
}

std::vector<Vector2> checkSpecialMoves(ChessSet *currentSet, Piece *chosenPiece)
{
    std::vector<Vector2> vect;
    bool enableSpecial = false;
    Vector2 position = chosenPiece->getPosition();
    switch (chosenPiece->getId())
    {
    case PIECE::PAWN:
        if (position.y == 1 || position.y == 6)
            enableSpecial = true;
        break;
    case PIECE::KING:
        // todo
        break;
    default:
        return vect;
    }
    if (enableSpecial) {
        for (auto move : chosenPiece->getSpecialMoves())
        {
            Vector2 v = Vector2Add(chosenPiece->getPosition(), move);
            vect.push_back(v);
            v = Vector2Scale(v, SQUARE_SIZE);
            DrawRectangle(v.x, v.y, SQUARE_SIZE, SQUARE_SIZE, HIGHLIGHT_SPECIAL);
        }
    }
    return vect;
}

#endif