#include "raylib.h"
#include "Miscellaneous.h"
#include "ChessBoard.h"

int main()
{

    InitWindow(WINDOW_SIZE, WINDOW_SIZE, "CHESS ENGINE");

    ChessBoard *board = new ChessBoard(WINDOW_SIZE);
    Piece *chosenPiece;
    bool pieceSelected = false;
    bool turn = WHITE_PLAYER;

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        board->draw(COLORS[0], COLORS[1]);

        Vector2 mousePostion = GetMousePosition();
        int squareX = mousePostion.x / SQUARE_SIZE;
        int squareY = mousePostion.y / SQUARE_SIZE;
        Vector2 boardPosition = {static_cast<float>(squareY), static_cast<float>(squareX)};
        ChessSet *currentSet = (turn) ? board->getBlackSet() : board->getWhiteSet();
        ChessSet *opposingSet = (!turn) ? board->getBlackSet() : board->getWhiteSet();

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            if (!pieceSelected)
                chosenPiece = currentSet->getPieceByPosition(boardPosition);
            if (chosenPiece != nullptr)
            {
                pieceSelected = true;
                chosenPiece->setToBeDrawn();
                chosenPiece->draw(chosenPiece->getPixelPosition(mousePostion, boardPosition));
                chosenPiece->unsetToBeDrawn();
            }
        }
        if (pieceSelected && IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        {
            pieceSelected = false;
            board->updatePosition(chosenPiece->getPosition(), boardPosition);
            chosenPiece->setPosition(boardPosition);
            chosenPiece->setToBeDrawn();
            chosenPiece = nullptr;
            board->printState();
        }
        EndDrawing();
    }
    delete board;
    return 0;
}