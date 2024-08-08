#include "ChessBoard.h"
#include "King.h"
#include "Queen.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Pawn.h"

#include <iostream>

struct PlayerSet
{
    PLAYER_COLORS color;
    King *king;
    Queen *queen;
    Rook *rook[2];
    Knight *knight[2];
    Bishop *bishop[2];
    Pawn *pawn[8];
    PlayerSet(PLAYER_COLORS col) : color(col)
    {
        if (col == WHITE_PLAYER)
        {
            king = new King({7, 3}, WHITE_PLAYER);
            queen = new Queen({7, 4}, WHITE_PLAYER);
            rook[0] = new Rook({7, 0}, WHITE_PLAYER), rook[1] = new Rook({7, 7}, WHITE_PLAYER);
            knight[0] = new Knight({7, 1}, WHITE_PLAYER), knight[1] = new Knight({7, 6}, WHITE_PLAYER);
            bishop[0] = new Bishop({7, 2}, WHITE_PLAYER), bishop[1] = new Bishop({7, 5}, WHITE_PLAYER);
            for (int i = 0; i < 8; i++)
                pawn[i] = new Pawn({6, static_cast<float>(i)}, WHITE_PLAYER);
        }
        else
        {
            king = new King({0, 3}, BLACK_PLAYER);
            queen = new Queen({0, 4}, BLACK_PLAYER);
            rook[0] = new Rook({0, 0}, BLACK_PLAYER), rook[1] = new Rook({0, 7}, BLACK_PLAYER);
            knight[0] = new Knight({0, 1}, BLACK_PLAYER), knight[1] = new Knight({0, 6}, BLACK_PLAYER);
            bishop[0] = new Bishop({0, 2}, BLACK_PLAYER), bishop[1] = new Bishop({0, 5}, BLACK_PLAYER);
            for (int i = 0; i < 8; i++)
                pawn[i] = new Pawn({1, static_cast<float>(i)}, BLACK_PLAYER);
        }
    }
    void drawSet()
    {
        king->draw();
        queen->draw();
        rook[0]->draw(), rook[1]->draw();
        knight[0]->draw(), knight[1]->draw();
        bishop[0]->draw(), bishop[1]->draw();
        for (int i = 0; i < 8; i++)
            pawn[i]->draw();
    }
    void clear()
    {
        delete king;
        delete queen;
        delete rook[0], delete rook[1];
        delete bishop[0], delete bishop[1];
        delete knight[0], delete knight[1];
        for (int i = 0; i < 8; i++)
            delete pawn[i];
    }
};

int main()
{
    const Color COLORS[2] = {{0, 0, 0, 255}, {216, 202, 176, 255}};

    InitWindow(WINDOW_SIZE, WINDOW_SIZE, "CHESS ENGINE");

    ChessBoard *chessBoard = new ChessBoard(static_cast<float>(WINDOW_SIZE));
    PlayerSet *whiteSet = new PlayerSet(WHITE_PLAYER);
    PlayerSet *blackSet = new PlayerSet(BLACK_PLAYER);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        chessBoard->drawChessBoard(COLORS[WHITE_PLAYER], COLORS[BLACK_PLAYER]);

        whiteSet->drawSet();
        blackSet->drawSet();
        Vector2 mousePostion = GetMousePosition();
        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
        {
            int posX = mousePostion.y / SQUARE_SIZE;
            int posY = mousePostion.x / SQUARE_SIZE;
            std::cout << posX << ' ' << posY << '\n';
        }

        EndDrawing();
    }

    delete chessBoard;
    whiteSet->clear();
    blackSet->clear();
    delete whiteSet;
    delete blackSet;
    return 0;
}