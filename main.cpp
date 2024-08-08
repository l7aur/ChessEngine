#include "ChessBoard.h"
#include "Knight.h"

int main()
{
    const int WINDOW_SIZE = 800;
    // const Color COLORS[2] = {{0, 0, 0, 255}, {216, 202, 176, 255}};
    const Color COLORS[2] = {{255, 0, 0, 255}, {0, 0, 255, 255}};

    ChessBoard *chessBoard = new ChessBoard(static_cast<float>(WINDOW_SIZE));
    Knight *black_knight = new Knight({0, 0}, BLACK_PLAYER);

    InitWindow(WINDOW_SIZE, WINDOW_SIZE, "CHESS ENGINE");
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        chessBoard->drawChessBoard(COLORS[WHITE_PLAYER], COLORS[BLACK_PLAYER]);
        black_knight->draw(chessBoard->at(0, 0));
        EndDrawing();
    }

    delete chessBoard;
    // delete black_knight;
    return 0;
}