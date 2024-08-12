#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <algorithm>

#include "ChessBoard.h"
#include "ChessSet.h"
#include "raymath.h"

template <class T> void VectorAppend(std::vector<T> & v1, std::vector<T> v2) {
    v1.insert(v1.end(), v2.begin(), v2.end());
} 

bool find(std::vector<Vector2> v, Vector2 x)
{
    // check if a vector2D is part of an array
    for (auto i : v)
        if (Vector2Equals(i, x))
            return true;
    return false;
}

int convertVectorToDirection(Vector2 v)
{
    // normalize vector
    v.x = (v.x > 0) ? 1 : (v.x < 0) ? -1
                                    : 0;
    v.y = (v.y > 0) ? 1 : (v.y < 0) ? -1
                                    : 0;
    return Vector2Equals(v, {0, -1})    ? 0   // N
           : Vector2Equals(v, {1, -1})  ? 1   // NE
           : Vector2Equals(v, {1, 0})   ? 2   // E
           : Vector2Equals(v, {1, 1})   ? 3   // SE
           : Vector2Equals(v, {0, 1})   ? 4   // S
           : Vector2Equals(v, {-1, 1})  ? 5   // SV
           : Vector2Equals(v, {-1, 0})  ? 6   // V
           : Vector2Equals(v, {-1, -1}) ? 7   // NV
                                        : -1; // UNDEFINED
}

std::vector<Vector2> highlightAllowedMoves(ChessBoard *chessBoard, ChessSet *currentSet, ChessSet *opposingSet, Piece *chosenPiece)
{
    std::vector<Vector2> v;
    bool directions[] = {1, 1, 1, 1, 1, 1, 1, 1}; // n, ne, e, se, s, ...
    for (Vector2 allowedM : chosenPiece->getMoves())
    {

        Vector2 boardPos = Vector2Add(chosenPiece->getPosition(), allowedM);
        Vector2 pixelPos = Vector2Scale(boardPos, SQUARE_SIZE);
        Piece *inTargetPos = opposingSet->findPieceByPosition(boardPos);
        int currentDirection = convertVectorToDirection(allowedM);
        if (directions[currentDirection])
        {
            if (inTargetPos != nullptr)
            {
                directions[currentDirection] = 0;
                if (chosenPiece->getId() == PIECE::KNIGHT)
                    directions[currentDirection] = 1;
                continue;
            }
            inTargetPos = currentSet->findPieceByPosition(boardPos);
            if (inTargetPos != nullptr)
            {
                directions[currentDirection] = 0;
                if (chosenPiece->getId() == PIECE::KNIGHT)
                    directions[currentDirection] = 1;
                continue;
            }
            DrawRectangle(pixelPos.x, pixelPos.y, SQUARE_SIZE, SQUARE_SIZE, HIGHLIGHT_AVAILABLE_EMPTY);
            if (chessBoard->isInside(boardPos))
                v.push_back(boardPos);
        }
    }
    return v;
}

std::vector<Vector2> highlightAttackMoves(ChessSet *opposingSet, Piece *chosenPiece)
{
    //todo
    std::vector<Vector2> vect;
    return vect;
}

std::vector<Vector2> highlightSpecialMoves(ChessSet *currentSet, ChessSet *opposingSet, Piece *chosenPiece)
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
    if (enableSpecial)
    {
        for (auto move : chosenPiece->getSpecialMoves())
        {
            Vector2 boardPos = Vector2Add(chosenPiece->getPosition(), move);
            if (currentSet->findPieceByPosition(boardPos) ||
                opposingSet->findPieceByPosition(boardPos))
            {
                enableSpecial = false;
                break;
            }
            vect.push_back(boardPos);
        }
    }
    if (enableSpecial)
        for (auto i : vect)
        {
            Vector2 v = Vector2Scale(i, SQUARE_SIZE);
            DrawRectangle(v.x, v.y, SQUARE_SIZE, SQUARE_SIZE, HIGHLIGHT_SPECIAL);
        }
    return vect;
}

#endif