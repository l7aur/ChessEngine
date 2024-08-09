#include "ChessBoard.h"
#include "King.h"
#include "Queen.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Pawn.h"

#include "raymath.h"

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
        if (king->toBeDrawn)
            king->draw(king->computeBordPosition());
        if (queen->toBeDrawn)
            queen->draw(queen->computeBordPosition());
        for (int i = 0; i < 2; i++)
            if (rook[i]->toBeDrawn)
                rook[i]->draw(rook[i]->computeBordPosition());
        for (int i = 0; i < 2; i++)
            if (knight[i]->toBeDrawn)
                knight[i]->draw(knight[i]->computeBordPosition());
        for (int i = 0; i < 2; i++)
            if (bishop[i]->toBeDrawn)
                bishop[i]->draw(bishop[i]->computeBordPosition());
        for (int i = 0; i < 8; i++)
            if (pawn[i]->toBeDrawn)
                pawn[i]->draw(pawn[i]->computeBordPosition());
    }
    Piece *loopThrough(Vector2 pos)
    {
        if (Vector2Equals(king->getPosition(), pos))
            return king;
        if (Vector2Equals(queen->getPosition(), pos))
            return queen;
        for (int i = 0; i < 2; i++)
            if (Vector2Equals(rook[i]->getPosition(), pos))
                return rook[i];
        for (int i = 0; i < 2; i++)
            if (Vector2Equals(knight[i]->getPosition(), pos))
                return knight[i];
        for (int i = 0; i < 2; i++)
            if (Vector2Equals(bishop[i]->getPosition(), pos))
                return bishop[i];
        for (int i = 0; i < 8; i++)
            if (Vector2Equals(pawn[i]->getPosition(), pos))
                return pawn[i];
        return nullptr;
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

Rectangle computeRectangle(Vector2 mouse, Vector2 board)
{
    Rectangle r;
    Vector2 boardVect = Vector2Scale(board, 100);
    Vector2 displacement = Vector2Subtract(mouse, boardVect);
    r.y = mouse.x - displacement.x + PADDING;
    r.x = mouse.y - displacement.y + PADDING;
    r.height = r.width = SQUARE_SIZE - 2 * PADDING;
    return r;
}

int main()
{
    const Color COLORS[2] = {{0, 0, 0, 255}, {216, 202, 176, 255}};

    InitWindow(WINDOW_SIZE, WINDOW_SIZE, "CHESS ENGINE");

    ChessBoard *chessBoard = new ChessBoard(static_cast<float>(WINDOW_SIZE));
    PlayerSet *whiteSet = new PlayerSet(WHITE_PLAYER);
    PlayerSet *blackSet = new PlayerSet(BLACK_PLAYER);
    Piece *chosenPiece;
    bool pieceSelected = false;
    bool turn = WHITE_PLAYER;

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        chessBoard->drawChessBoard(COLORS[WHITE_PLAYER], COLORS[BLACK_PLAYER]);

        whiteSet->drawSet();
        blackSet->drawSet();
        Vector2 mousePostion = GetMousePosition();
        int squareX = mousePostion.y / SQUARE_SIZE;
        int squareY = mousePostion.x / SQUARE_SIZE;
        Vector2 boardPosition = {static_cast<float>(squareX), static_cast<float>(squareY)};

        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
        {
            PlayerSet *currentSet = (turn) ? blackSet : whiteSet;
            if (!pieceSelected)
                chosenPiece = currentSet->loopThrough(boardPosition);
            if (chosenPiece != nullptr)
            {
                chosenPiece->draw(computeRectangle(mousePostion, boardPosition));
                pieceSelected = true;
                chosenPiece->toBeDrawn = false;
            }
            else
                std::cout << "no piece detected!\n";
        }
        if (pieceSelected && IsMouseButtonReleased(MOUSE_BUTTON_RIGHT))
        {
            if(!Vector2Equals(boardPosition, chosenPiece->getPosition()))
                turn = !turn;
            chosenPiece->setPosition(boardPosition);
            chosenPiece->toBeDrawn = true;
            pieceSelected = false;
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