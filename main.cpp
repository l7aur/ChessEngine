#include "Functions.h"

int main()
{
    InitWindow(WINDOW_SIZE, WINDOW_SIZE, "CHESS ENGINE");

    ChessBoard *chessBoard = new ChessBoard(static_cast<float>(WINDOW_SIZE));
    ChessSet *whiteSet = new ChessSet(WHITE_PLAYER);
    ChessSet *blackSet = new ChessSet(BLACK_PLAYER);

    Piece *chosenPiece;
    bool pieceSelected = false;
    bool turn = WHITE_PLAYER;
    std::vector<Vector2> moves;
    bool inCheck = false;

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

        inCheck = hihglightCheck(currentSet, opposingSet);
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            if (!pieceSelected)
                chosenPiece = currentSet->findPieceByPosition(boardPosition);
            if (chosenPiece != nullptr)
            {
                chosenPiece->draw(chosenPiece->computeBoardPosition(mousePostion, boardPosition));
                moves.clear();
                VectorAppend(moves, highlightAllowedMoves(chessBoard, currentSet, opposingSet, chosenPiece));
                VectorAppend(moves, highlightSpecialMoves(currentSet, opposingSet, chosenPiece));
                VectorAppend(moves, highlightAttackMoves(chessBoard, currentSet, opposingSet, chosenPiece));
                pieceSelected = true;
                chosenPiece->toBeDrawn = false;
            }
            else
                std::cerr << "\nNo piece detected!\n";
        }
        if (pieceSelected && IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        {
            if (nullptr == currentSet->findPieceByPosition(boardPosition) && find(moves, boardPosition))
            {
                Piece *p = opposingSet->findPieceByPosition(boardPosition);
                if (p != nullptr && p->getId() != PIECE::KING)
                    p->setPosition(LOST_PIECE_POSITION);
                turn = !turn;
                if ((p == nullptr || p->getId() != PIECE::KING))
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