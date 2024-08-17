#include "raylib.h"
#include "raymath.h"
#include "ChessBoard.h"
#include "Methods.h"
#include <queue>

int main()
{
    InitWindow(WINDOW_SIZE, WINDOW_SIZE, "CHESS ENGINE");

    ChessBoard *board = new ChessBoard(WINDOW_SIZE);
    Piece *chosenPiece;
    King *whiteKing = (King *)board->getWhiteSet()->getPieceByPosition({7, 3});
    King *blackKing = (King *)board->getBlackSet()->getPieceByPosition({0, 3});
    bool pieceSelected = false;
    bool turn = WHITE_PLAYER;
    std::vector<Vector2> goToSpots;
    std::vector<Vector2> goToSpecialSpots;

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        board->draw(COLORS[0], COLORS[1]);

        Vector2 mousePostion = GetMousePosition();
        int squareX = mousePostion.x / SQUARE_SIZE;
        int squareY = mousePostion.y / SQUARE_SIZE;
        Vector2 boardPosition = {static_cast<float>(squareY), static_cast<float>(squareX)};
        ChessSet *currentSet = (!turn) ? board->getWhiteSet() : board->getBlackSet();
        ChessSet *opposingSet = (turn) ? board->getWhiteSet() : board->getBlackSet();
        PIECE opponentKingID = (turn) ? W_KING : B_KING;
        PIECE currentKingID = (turn) ? B_KING : W_KING;

        bool currentKingInCheck = getCheckState(board, opposingSet, (turn) ? blackKing : whiteKing);
        if (currentKingInCheck)
            DrawRectangle(((turn) ? blackKing : whiteKing)->getPosition().y * SQUARE_SIZE,
                          ((turn) ? blackKing : whiteKing)->getPosition().x * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE, HIGHLIGHT_CHECK);
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
                goToSpots.clear();
                goToSpots = getAvailable(board, chosenPiece);
                highlight(goToSpots, HIGHLIGHT_AVAILABLE_EMPTY);
                std::vector<Vector2> v = getAttack(board, chosenPiece);
                highlight(v, HIGHLIGHT_AVAILABLE_ATTACK);
                VectorAppend(goToSpots, v);
                goToSpecialSpots = getSpecial(board, chosenPiece);
                highlight(goToSpecialSpots, HIGHLIGHT_SPECIAL);
            }
        }
        if (pieceSelected && IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        {
            if (!Vector2Equals(boardPosition, chosenPiece->getPosition()))
            {
                bool kingCastle = false;
                if (!find(goToSpecialSpots, boardPosition))
                {
                    if (!find(goToSpots, boardPosition))
                        goto end;
                }
                else
                    kingCastle = true;
                BoardPlace *desiredPlace = board->at(boardPosition);
                if (isOponent(desiredPlace, board->at(chosenPiece->getPosition())) && desiredPlace->id != opponentKingID) // opponent has piece there
                {
                    Vector2 oldPos = chosenPiece->getPosition();
                    board->updatePosition(chosenPiece->getPosition(), boardPosition);
                    chosenPiece->setPosition(boardPosition);
                    if (!(currentKingInCheck = getCheckState(board, opposingSet, (turn) ? blackKing : whiteKing)))
                    {
                        removeOpponentsPiece((turn) ? board->getWhiteSet() : board->getBlackSet(), boardPosition, board->at(oldPos));
                        if (board->getAbstractBoard()[static_cast<int>(boardPosition.x)][static_cast<int>(boardPosition.y)].id == B_KING ||
                            board->getAbstractBoard()[static_cast<int>(boardPosition.x)][static_cast<int>(boardPosition.y)].id == W_KING)
                            ((King *)chosenPiece)->unsetCanCastle();
                        turn = !turn;
                    }
                    else
                    {
                        board->updatePosition(chosenPiece->getPosition(), oldPos);
                        chosenPiece->setPosition(oldPos);
                    }
                }
                else if (desiredPlace->id == DON_T_CARE)
                {
                    Vector2 oldPos = chosenPiece->getPosition();
                    board->updatePosition(chosenPiece->getPosition(), boardPosition);
                    chosenPiece->setPosition(boardPosition);
                    if (!(currentKingInCheck = getCheckState(board, opposingSet, (turn) ? blackKing : whiteKing)))
                    {
                        turn = !turn;
                        if (kingCastle && board->getAbstractBoard()[static_cast<int>(boardPosition.x)][static_cast<int>(boardPosition.y)].id == currentKingID)
                        {
                            if (!((King *)chosenPiece)->getCanCastle())
                                goto end;
                            if (Vector2Equals(boardPosition, {0, 1}) || Vector2Equals(boardPosition, {7, 1})) // left castle
                            {
                                Piece *rook = currentSet->getPieceByPosition({boardPosition.x, 0});
                                Vector2 roldPos = rook->getPosition();
                                board->updatePosition(rook->getPosition(), {boardPosition.x, 2});
                                rook->setPosition({boardPosition.x, 2});
                                if (!(currentKingInCheck = getCheckState(board, opposingSet, (turn) ? blackKing : whiteKing)))
                                {
                                    ((King *)chosenPiece)->unsetCanCastle();
                                }
                                else
                                {
                                    board->updatePosition(rook->getPosition(), roldPos);
                                    rook->setPosition(roldPos);
                                }
                            }
                            if (Vector2Equals(boardPosition, {0, 5}) || Vector2Equals(boardPosition, {7, 5})) // right castle
                            {
                                Piece *rook = currentSet->getPieceByPosition({boardPosition.x, 7});
                                Vector2 roldPos = rook->getPosition();
                                board->updatePosition(rook->getPosition(), {boardPosition.x, 4});
                                rook->setPosition({boardPosition.x, 4});
                                if (!(currentKingInCheck = getCheckState(board, opposingSet, (turn) ? blackKing : whiteKing)))
                                {
                                    ((King *)chosenPiece)->unsetCanCastle();
                                }
                                else
                                {
                                    board->updatePosition(rook->getPosition(), roldPos);
                                    rook->setPosition(roldPos);
                                }
                            }
                        }
                        if (board->getAbstractBoard()[static_cast<int>(boardPosition.x)][static_cast<int>(boardPosition.y)].id == B_KING ||
                            board->getAbstractBoard()[static_cast<int>(boardPosition.x)][static_cast<int>(boardPosition.y)].id == W_KING)
                            ((King *)chosenPiece)->unsetCanCastle();
                    }
                    else
                    {
                        board->updatePosition(chosenPiece->getPosition(), oldPos);
                        chosenPiece->setPosition(oldPos);
                    }
                }
            }
        end:
            chosenPiece->setToBeDrawn();
            pieceSelected = false;
            chosenPiece = nullptr;
            board->printState();
        }
        EndDrawing();
    }
    delete board;
    return 0;
}