#ifndef METHODS_H
#define METHODS_H

#include "raylib.h"
#include "ChessBoard.h"

std::vector<Vector2> getAvailable(ChessBoard *board, Piece *piece);
std::vector<Vector2> getAttack(ChessBoard *board, Piece *piece);
std::vector<Vector2> getSpecial(ChessBoard *board, Piece *piece);
void highlight(std::vector<Vector2> v, Color c);
bool getCheckState(ChessBoard *board, ChessSet *opposingSet, King *king);
void removeOpponentsPiece(ChessSet * opposingSet, Vector2 boardPosition, BoardPlace *desiredPlace);

#endif