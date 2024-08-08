#include "ChessBoard.h"

ChessBoard::ChessBoard(float size)
{
    for(int i = 0; i < 8; i++)
        for(int j = 0; j < 8; j++) {
            board[i][j].position.y = i * SQUARE_SIZE;
            board[i][j].position.x = j * SQUARE_SIZE;
            board[i][j].position.width = board[i][j].position.height = SQUARE_SIZE;
            board[i][j].color = (i + j) % 2;
        }
}

void ChessBoard::drawChessBoard(Color firstColor, Color secondColor)
{
    for(int i = 0; i < 8; i++)
        for(int j = 0; j < 8; j++) {
            Color color = (board[i][j].color == 0) ? firstColor : secondColor;
            DrawRectangle(board[i][j].position.x, board[i][j].position.y, board[i][j].position.width, board[i][j].position.height, color);
        }
}

BoardPlace ChessBoard::at(int i, int j)
{
    if(i < 0 || i > 7)
        return BoardPlace();
    if(j < 0 || j > 7)
        return BoardPlace();
    return this->board[i][j];
}
