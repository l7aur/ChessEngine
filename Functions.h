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

bool find(std::vector<Vector2> v, Vector2 x);
int convertVectorToDirection(Vector2 v);
bool hihglightCheck(ChessSet *currentSet, ChessSet * opposingSet);
std::vector<Vector2> highlightAllowedMoves(ChessBoard *chessBoard, ChessSet *currentSet, ChessSet *opposingSet, Piece *chosenPiece);
std::vector<Vector2> highlightAttackMoves(ChessBoard * chessBoard, ChessSet *currentSet, ChessSet *opposingSet, Piece *chosenPiece);
std::vector<Vector2> highlightSpecialMoves(ChessSet *currentSet, ChessSet *opposingSet, Piece *chosenPiece);

#endif