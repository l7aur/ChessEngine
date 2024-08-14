#ifndef MISCELLANEOUS_H
#define MISCELLANEOUS_H

#include "raylib.h"

const int WINDOW_SIZE = 800;
const int SQUARE_SIZE = WINDOW_SIZE / 8;
const int SPRITE_SIZE = 32;
const int PADDING = 5;
const Vector2 LOST_PIECE_POSITION{100, 100};
const Color COLORS[2] = {{0, 0, 0, 255}, {216, 202, 176, 255}};
const Color HIGHLIGHT_AVAILABLE_EMPTY = {0, 255, 0, 200};
const Color HIGHLIGHT_AVAILABLE_ATTACK = {255, 0, 0, 200};
const Color HIGHLIGHT_SPECIAL = {0, 0, 255, 200};

enum PLAYER_COLORS
{
    // no more than 2
    WHITE_PLAYER,
    BLACK_PLAYER
};

enum PIECE
{
    DON_T_CARE,
    B_KING,
    B_QUEEN,
    B_BISHOP,
    B_ROOK,
    B_KNIGHT,
    B_PAWN,
    W_KING,
    W_QUEEN,
    W_BISHOP,
    W_ROOK,
    W_KNIGHT,
    W_PAWN
};

struct BoardPlace
{
    Rectangle rectangle{};
    bool rectangleColor;
    PIECE id;
    BoardPlace()
    {
        rectangle = {0.0f, 0.0f, 0.0f, 0.0f};
        rectangleColor = 0; 
        id = PIECE::DON_T_CARE;
    }
};

#endif