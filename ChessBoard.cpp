#include "ChessBoard.h"

ChessBoard::ChessBoard(float size)
{
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
        {
            board[i][j].position.x = i * SQUARE_SIZE;
            board[i][j].position.y = j * SQUARE_SIZE;
            board[i][j].position.width = board[i][j].position.height = SQUARE_SIZE;
            board[i][j].color = (i + j) % 2;
        }
}

void ChessBoard::drawChessBoard(Color firstColor, Color secondColor) const
{
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
        {
            Color color = (board[i][j].color == 0) ? firstColor : secondColor;
            DrawRectangle(board[i][j].position.x, board[i][j].position.y, board[i][j].position.width, board[i][j].position.height, color);
        }
}

bool ChessBoard::isInside(Vector2 v) const
{
    if (v.x < 0 || v.y < 0 || v.x > 7 || v.y > 7)
        return false;
    return true;
}

BoardPlace ChessBoard::at(int i, int j) const
{
    if (i < 0 || i > 7)
        throw std::invalid_argument("\nCHESS BOARD\nPosition does not exist on the board\n");
    if (j < 0 || j > 7)
        throw std::invalid_argument("\nCHESS BOARD\nPosition does not exist on the board\n");
    return this->board[i][j];
}