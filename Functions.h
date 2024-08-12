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

int convertVectorToDirection(Vector2 v)
{
    v.x = (v.x > 0) ? 1 : (v.x < 0) ? -1
                                    : 0;
    v.y = (v.y > 0) ? 1 : (v.y < 0) ? -1
                                    : 0;
    if (v.x == 0 && v.y == -1)
        return 0; // n
    if (v.x == 1 && v.y == -1)
        return 1; // ne
    if (v.x == 1 && v.y == 0)
        return 2; // e
    if (v.x == 1 && v.y == 1)
        return 3; // se
    if (v.x == 0 && v.y == 1)
        return 4; // s
    if (v.x == -1 && v.y == 1)
        return 5; // sv
    if (v.x == -1 && v.y == 0)
        return 6; // v
    if (v.x == -1 && v.y == -1)
        return 7; // nv
    return -1;
}

bool isInsideBoard(Vector2 v)
{
    if (v.x < 0 || v.y < 0 || v.x > 7 || v.y > 7)
        return false;
    return true;
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
            if (isInsideBoard(boardPos))
                v.push_back(boardPos);
        }
    }
    return v;
}

std::vector<Vector2> highlightAttackMoves(ChessSet *opposingSet, Piece *chosenPiece)
{
    std::vector<Vector2> vect;
    return vect;
}

std::vector<Vector2> highlightSpecialMoves(ChessSet *currentSet, Piece *chosenPiece)
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
            Vector2 v = Vector2Add(chosenPiece->getPosition(), move);
            vect.push_back(v);
            v = Vector2Scale(v, SQUARE_SIZE);
            DrawRectangle(v.x, v.y, SQUARE_SIZE, SQUARE_SIZE, HIGHLIGHT_SPECIAL);
        }
    }
    return vect;
}

#endif