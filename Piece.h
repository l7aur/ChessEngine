#ifndef PIECE_H
#define PIECE_H

#include "raylib.h"
#include "Types.h"
#include "ChessBoard.h"
#include <vector>
#include <algorithm>

class Piece
{
public:
    bool isInsideBoard() const;
    void draw(Rectangle boardPosition) const;
    Rectangle computeBoardPosition() const;
    Rectangle computeBoardPosition(Vector2 mouse, Vector2 board) const;
    inline Vector2 getPosition() const { return this->position; };
    inline void setPosition(Vector2 newPos) { this->position = newPos; };
    inline std::vector<Vector2> getMoves() const { return this->moves; };
    inline std::vector<Vector2> getSpecialMoves() const { return this->specialMoves; };
    inline PIECE getId() const { return this->id; };
    ~Piece();

    bool toBeDrawn{true};

protected:
    Texture2D sprite{};
    Vector2 position{};
    std::vector<Vector2> moves{};
    std::vector<Vector2> specialMoves{};
    std::vector<Vector2> attackMoves{};
    PIECE id{DON_T_CARE};
private:
};

#endif