#ifndef PIECE_H
#define PIECE_H

#include "Miscellaneous.h"
#include "raylib.h"
#include <vector>

class Piece
{
public:
    Piece();
    inline Vector2 getPosition() const { return this->position; };
    Rectangle getPixelPosition() const;
    Rectangle getPixelPosition(Vector2 mouse, Vector2 board) const;
    void draw(Rectangle place) const;
    std::vector<Vector2> getAttack() const;
    std::vector<Vector2> getSpecial() const;
    std::vector<Vector2> getAvailable() const;
    inline void setPosition(Vector2 pos) { this->position = pos; };
    inline void setToBeDrawn() { this->toBeDrawn = true; };
    inline void unsetToBeDrawn() { this->toBeDrawn = false; };
    virtual ~Piece() {};

protected:
    Vector2 position{};
    Texture2D sprite{};
    std::vector<Vector2> allowedMoves;
    std::vector<Vector2> specialMoves;
    std::vector<Vector2> attackMoves;
    bool toBeDrawn{true};

private:
};
#endif