#include "ChessBoard.h"

int main()
{
    const int WINDOW_SIZE = 800;
    const Color COLORS[2] = {{0, 0, 0, 255}, {216, 202, 176, 255}};

    ChessBoard *chessBoard = new ChessBoard(static_cast<float>(WINDOW_SIZE));

    InitWindow(WINDOW_SIZE, WINDOW_SIZE, "CHESS ENGINE");
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        chessBoard->drawChessBoard(COLORS[WHITE_PLAYER], COLORS[BLACK_PLAYER]);
        EndDrawing();
    }

    delete chessBoard;
    return 0;
}