#include "Miscellaneous.h"
#include "raymath.h"

bool isInsideBoard(Vector2 v)
{
    return !(v.x < 0 || v.y < 0 || v.x > 7 || v.y > 7);
}

bool isOponent(BoardPlace *place1, BoardPlace *place2)
{
    if (place1->id == DON_T_CARE || place2->id == DON_T_CARE)
        return false;
    if (place1->id <= B_PAWN && place2->id > B_PAWN)
        return true;
    if (place1->id > B_PAWN && place2->id <= B_PAWN)
        return true;
    return false;
}

bool find(std::vector<Vector2> &v, Vector2 elem)
{
    for (auto i : v)
        if (Vector2Equals(i, elem))
            return true;
    return false;
}
