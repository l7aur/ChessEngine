#include "ChessBoard.h"
#include "ChessSet.h"

#include "raymath.h"

#include <iostream>

void highlightAllowedMoves(ChessBoard *chessBoard, ChessSet *currentSet, ChessSet *opposingSet, Piece *chosenPiece);

int main()
{
    const Vector2 LOST_PIECE_POSITION{100, 100};
    InitWindow(WINDOW_SIZE, WINDOW_SIZE, "CHESS ENGINE");

    ChessBoard *chessBoard = new ChessBoard(static_cast<float>(WINDOW_SIZE));
    ChessSet *whiteSet = new ChessSet(WHITE_PLAYER);
    ChessSet *blackSet = new ChessSet(BLACK_PLAYER);

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
            ChessSet *currentSet = (turn) ? blackSet : whiteSet;
            ChessSet *opposingSet = (!turn) ? blackSet : whiteSet;
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            if (!pieceSelected)
                chosenPiece = currentSet->findPieceByPosition(boardPosition);
            if (chosenPiece != nullptr)
            {
                chosenPiece->draw(chosenPiece->computeBoardPosition(mousePostion, boardPosition));
                highlightAllowedMoves(chessBoard, currentSet, opposingSet, chosenPiece);
                pieceSelected = true;
                chosenPiece->toBeDrawn = false;
            }
            else
                std::cout << "\nNo piece detected!\n";
        }
        if (pieceSelected && IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        {
            if (!Vector2Equals(boardPosition, chosenPiece->getPosition()) && 
            nullptr == currentSet->findPieceByPosition(boardPosition))
            {
                Piece * p = opposingSet->findPieceByPosition(boardPosition);
                if(p != nullptr)
                    p->setPosition(LOST_PIECE_POSITION);

                turn = !turn;
                // chosenPiece->updatePreviousPosition();
                chosenPiece->setPosition(boardPosition);
            }
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

void highlightAllowedMoves(ChessBoard *chessBoard, ChessSet *currentSet, ChessSet *opposingSet, Piece *chosenPiece)
{
    for (Vector2 allowedM : chosenPiece->getMoves())
    {
        Vector2 boardPos = Vector2Add(chosenPiece->getPosition(), allowedM);
        Vector2 pixelPos = Vector2Scale(boardPos, SQUARE_SIZE);
        Piece *inTargetPos = opposingSet->findPieceByPosition(boardPos);
        if (inTargetPos != nullptr)
            DrawRectangle(pixelPos.x, pixelPos.y, SQUARE_SIZE, SQUARE_SIZE, HIGHLIGHT_AVAILABLE_ATTACK);
        else
        {
            inTargetPos = currentSet->findPieceByPosition(boardPos);
            if (inTargetPos == nullptr)
                DrawRectangle(pixelPos.x, pixelPos.y, SQUARE_SIZE, SQUARE_SIZE, HIGHLIGHT_AVAILABLE_EMPTY);
        }
    }
}
