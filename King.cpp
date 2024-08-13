#include "King.h"
#include "raymath.h"
#include <iostream>

King::King(Vector2 pos, bool color)
{
    this->id = PIECE::KING;
    this->position = pos;
    if(!this->isInsideBoard())
        throw std::invalid_argument("\nKING\nReceived wrong value for position!\n");
    this->moves.push_back({0, 1});
    this->moves.push_back({0, -1});
    this->moves.push_back({1, 1});
    this->moves.push_back({1, -1});
    this->moves.push_back({1, 0});
    this->moves.push_back({-1, 0});
    this->moves.push_back({-1, 1});
    this->moves.push_back({-1, -1});
    this->specialMoves.push_back({2, 0});
    this->specialMoves.push_back({-2, 0});
    this->attackMoves = this->moves;
    sprite = (color == WHITE_PLAYER) ? LoadTexture("Sprites\\white_king.png") : LoadTexture("Sprites\\black_king.png");
}

// bool King::checkForCheck(Piece * piece, std::vector<Vector2> moves) const
// {
//     for(auto m: moves)
//         if(Vector2Equals(Vector2Add(piece->getPosition(), m), this->position)) {
//             this->hihglightCheck();
//             std::cout << "ayay\n";
//             return true;
//         }
//     return false;
// }

// void King::hihglightCheck() const
// {
//     DrawRectangle(this->position.x * SQUARE_SIZE, this->position.y * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE, HIGHLIGHT_AVAILABLE_ATTACK);
// }
