#include "raylib.h"
#include "raymath.h"
#include "ChessBoard.h"

void highlightAvailable(ChessBoard *board, Piece *piece);
void highlightAttack(ChessBoard *board, Piece *piece);
void highlightSpecial(ChessBoard *board, Piece *piece);
void removeOpponentsPiece(ChessBoard *board, Vector2 boardPosition, BoardPlace *desiredPlace, bool turn);

int main()
{
    InitWindow(WINDOW_SIZE, WINDOW_SIZE, "CHESS ENGINE");

    ChessBoard *board = new ChessBoard(WINDOW_SIZE);
    Piece *chosenPiece;
    bool pieceSelected = false;
    bool turn = WHITE_PLAYER;
    std::vector<Vector2> goToSpots;

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
                goToSpots = chosenPiece->getAvailable();
                highlightAvailable(board, chosenPiece);
                highlightAttack(board, chosenPiece);
                highlightSpecial(board, chosenPiece);
            }
        }
        if (pieceSelected && IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        {
            if (!Vector2Equals(boardPosition, chosenPiece->getPosition()))
            {
                BoardPlace *desiredPlace = board->at(boardPosition);
                if (isOponent(desiredPlace, board->at(chosenPiece->getPosition())) && desiredPlace->id != opponentKingID) // opponent has piece there
                {
                    removeOpponentsPiece(board, boardPosition, desiredPlace, turn);
                    board->updatePosition(chosenPiece->getPosition(), boardPosition);
                    chosenPiece->setPosition(boardPosition);
                    turn = !turn;
                }
                if (desiredPlace->id == DON_T_CARE)
                {
                    board->updatePosition(chosenPiece->getPosition(), boardPosition);
                    chosenPiece->setPosition(boardPosition);
                    turn = !turn;
                }
            }
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

void highlightAvailable(ChessBoard *board, Piece *piece)
{
    for (auto m : piece->getAvailable())
    {
        Vector2 newPos = Vector2Add(piece->getPosition(), m);
        if (board->at(newPos)->id == PIECE::DON_T_CARE)
            DrawRectangle(newPos.y * SQUARE_SIZE, newPos.x * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE, HIGHLIGHT_AVAILABLE_EMPTY);
    }
}

void highlightAttack(ChessBoard *board, Piece *piece)
{
    for (auto m : piece->getAttack())
    {
        Vector2 newPos = Vector2Add(piece->getPosition(), m);
        if (isOponent(board->at(piece->getPosition()), board->at(newPos)))
            DrawRectangle(newPos.y * SQUARE_SIZE, newPos.x * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE, HIGHLIGHT_AVAILABLE_ATTACK);
    }
}

void highlightSpecial(ChessBoard *board, Piece *piece)
{
    bool enableSpecial = false;
    int posX = static_cast<int>(piece->getPosition().x);
    int posY = static_cast<int>(piece->getPosition().y);
    BoardPlace(*abstractBoard)[8] = board->getAbstractBoard();
    switch (abstractBoard[posX][posY].id)
    {
    case PIECE::B_PAWN:
        if (posX == 1)
            enableSpecial = true;
        break;
    case PIECE::W_PAWN:
        if (posX == 6)
            enableSpecial = true;
        break;
    case PIECE::B_KING:
        if (posX == 0 && posY == 3)
            enableSpecial = true;
        break;
    case PIECE::W_KING:
        if (posX == 7 && posY == 3)
            enableSpecial = true;
        break;
    default:
        break;
    }
    if (enableSpecial)
        for (auto m : piece->getSpecial())
        {
            Vector2 newPos = Vector2Add(piece->getPosition(), m);
            posX = static_cast<int>(newPos.x);
            posY = static_cast<int>(newPos.y);
            if (abstractBoard[posX][posY].id != DON_T_CARE)
            {
                enableSpecial = false;
                break;
            }
        }

    if (enableSpecial)
        for (auto m : piece->getSpecial())
        {
            Vector2 newPos = Vector2Add(piece->getPosition(), m);
            posX = static_cast<int>(newPos.x);
            posY = static_cast<int>(newPos.y);
            DrawRectangle(posY * SQUARE_SIZE, posX * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE, HIGHLIGHT_SPECIAL);
        }
}

void removeOpponentsPiece(ChessBoard *board, Vector2 boardPosition, BoardPlace *desiredPlace, bool turn)
{
    desiredPlace->id = DON_T_CARE;
    std::vector<Piece *> &pieces = (turn) ? board->getWhiteSet()->getPiecesOnBoard() : board->getBlackSet()->getPiecesOnBoard();

    for (auto p = pieces.begin(); p != pieces.end(); p++)
        if (Vector2Equals((*p)->getPosition(), boardPosition))
        {
            pieces.erase(p);
            break;
        }
}
