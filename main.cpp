#include "ChessBoard.h"
#include "ChessSet.h"

#include "raymath.h"

#include <iostream>
#include <algorithm>

std::vector<Vector2> highlightAllowedMoves(ChessBoard *chessBoard, ChessSet *currentSet, ChessSet *opposingSet, Piece *chosenPiece);
std::vector<Vector2> checkSpecialMoves(ChessSet *currentSet, Piece *chosenPiece);

bool find(std::vector<Vector2> v, Vector2 x)
{
    for (auto i : v)
        if (Vector2Equals(i, x))
            return true;
    return false;
}

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
    std::vector<Vector2> allowedMoves;
    std::vector<Vector2> specialMoves;

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
                allowedMoves = highlightAllowedMoves(chessBoard, currentSet, opposingSet, chosenPiece);
                specialMoves = checkSpecialMoves(currentSet, chosenPiece);
                pieceSelected = true;
                chosenPiece->toBeDrawn = false;
            }
            else
                std::cout << "\nNo piece detected!\n";
        }
        if (pieceSelected && IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        {
            if (nullptr == currentSet->findPieceByPosition(boardPosition) &&
                (find(allowedMoves, boardPosition) || find(specialMoves, boardPosition)))
            {
                Piece *p = opposingSet->findPieceByPosition(boardPosition);
                if (p != nullptr)
                    p->setPosition(LOST_PIECE_POSITION);
                turn = !turn;
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

std::vector<Vector2> highlightAllowedMoves(ChessBoard *chessBoard, ChessSet *currentSet, ChessSet *opposingSet, Piece *chosenPiece)
{
    std::vector<Vector2> v;
    for (Vector2 allowedM : chosenPiece->getMoves())
    {
        Vector2 boardPos = Vector2Add(chosenPiece->getPosition(), allowedM);
        Vector2 pixelPos = Vector2Scale(boardPos, SQUARE_SIZE);
        Piece *inTargetPos = opposingSet->findPieceByPosition(boardPos);
        if (inTargetPos != nullptr)
        {
            DrawRectangle(pixelPos.x, pixelPos.y, SQUARE_SIZE, SQUARE_SIZE, HIGHLIGHT_AVAILABLE_ATTACK);
            v.push_back(boardPos);
        }
        else
        {
            inTargetPos = currentSet->findPieceByPosition(boardPos);
            if (inTargetPos == nullptr)
            {
                DrawRectangle(pixelPos.x, pixelPos.y, SQUARE_SIZE, SQUARE_SIZE, HIGHLIGHT_AVAILABLE_EMPTY);
                v.push_back(boardPos);
            }
        }
    }
    return v;
}

std::vector<Vector2> checkSpecialMoves(ChessSet *currentSet, Piece *chosenPiece)
{
    std::vector<Vector2> vect;
    bool enableSpecial = false;
    Vector2 position = chosenPiece->getPosition();
    switch (chosenPiece->getId())
    {
    case PIECE::PAWN:
        if (position.y == 1 || position.y == 6)
            enableSpecial = true;
        break;
    case PIECE::KING:
        // todo
        break;
    default:
        return vect;
    }
    if (enableSpecial) {
        for (auto move : chosenPiece->getSpecialMoves())
        {
            Vector2 v = Vector2Add(chosenPiece->getPosition(), move);
            vect.push_back(v);
            v = Vector2Scale(v, SQUARE_SIZE);
            DrawRectangle(v.x, v.y, SQUARE_SIZE, SQUARE_SIZE, HIGHLIGHT_SPECIAL);
        }
    }
    return vect;
}
