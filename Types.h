#ifndef TYPES_H
#define TYPES_H

#include "raylib.h"
#include <stdexcept>

const int WINDOW_SIZE = 800;
const int SQUARE_SIZE = WINDOW_SIZE / 8;
const int PADDING = 5;

enum PLAYER_COLORS { //no more than 2
    WHITE_PLAYER,
    BLACK_PLAYER
};

struct BoardPlace
{
    Rectangle position;
    int color;
    BoardPlace()
    {
        color = 0;
        position = {0.0f, 0.0f, 0.0f, 0.0f};
    };
};

#endif