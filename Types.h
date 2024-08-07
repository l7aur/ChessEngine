#ifndef TYPES_H
#define TYPES_H

#include "raylib.h"

enum PLAYER_COLORS {
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