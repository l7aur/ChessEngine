#include "ChessBoard.h"
#include "ChessSet.h"

#include "raymath.h"

#include <iostream>

int main()
{
    const Color COLORS[2] = {{0, 0, 0, 255}, {216, 202, 176, 255}};

    InitWindow(WINDOW_SIZE, WINDOW_SIZE, "CHESS ENGINE");

    ChessBoard *chessBoard = new ChessBoard(static_cast<float>(WINDOW_SIZE));
    ChessSet * whiteSet = new ChessSet(WHITE_PLAYER);
    ChessSet * blackSet = new ChessSet(BLACK_PLAYER);
    Piece *chosenPiece;
    bool pieceSelected = false;
    bool turn = WHITE_PLAYER;
    
    SetTargetFPS(30);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        chessBoard->drawChessBoard(COLORS[WHITE_PLAYER], COLORS[BLACK_PLAYER]);

        whiteSet->draw();
        blackSet->draw();
        Vector2 mousePostion = GetMousePosition();
        int squareX = mousePostion.x / SQUARE_SIZE;
        int squareY = mousePostion.y / SQUARE_SIZE;
        Vector2 boardPosition = {static_cast<float>(squareX), static_cast<float>(squareY)};
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            ChessSet *currentSet = (turn) ? blackSet : whiteSet;
            if (!pieceSelected)
                chosenPiece = currentSet->findPieceByPosition(boardPosition);
            if (chosenPiece != nullptr)
            {
                chosenPiece->draw(chosenPiece->computeBoardPosition(mousePostion, boardPosition));
                chosenPiece->highlightAllowedMoves(chessBoard);
                pieceSelected = true;
                chosenPiece->toBeDrawn = false;
            }
            else
                std::cout << "\nNo piece detected!\n";
        }
        if (pieceSelected && IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
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
    delete whiteSet;
    delete blackSet;
    return 0;
}