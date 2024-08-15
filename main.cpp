#include "raylib.h"
#include "raymath.h"
#include "ChessBoard.h"
#include <queue>

std::vector<Vector2> highlightAvailable(ChessBoard *board, Piece *piece);
std::vector<Vector2> highlightAttack(ChessBoard *board, Piece *piece);
std::vector<Vector2> highlightSpecial(ChessBoard *board, Piece *piece);
void removeOpponentsPiece(ChessBoard *board, Vector2 boardPosition, BoardPlace *desiredPlace, bool turn);

int main()
{
    InitWindow(WINDOW_SIZE, WINDOW_SIZE, "CHESS ENGINE");

    ChessBoard *board = new ChessBoard(WINDOW_SIZE);
    Piece *chosenPiece;
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
        // ChessSet *opposingSet = (turn) ? board->getWhiteSet() : board->getBlackSet();
        PIECE opponentKingID = (turn) ? W_KING : B_KING;
        PIECE currentKingID = (turn) ? B_KING : W_KING;

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
                goToSpots = highlightAvailable(board, chosenPiece);
                VectorAppend(goToSpots, highlightAttack(board, chosenPiece));
                goToSpecialSpots = highlightSpecial(board, chosenPiece);
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
                    removeOpponentsPiece(board, boardPosition, desiredPlace, turn);
                    board->updatePosition(chosenPiece->getPosition(), boardPosition);
                    chosenPiece->setPosition(boardPosition);
                    if (board->getAbstractBoard()[static_cast<int>(boardPosition.x)][static_cast<int>(boardPosition.y)].id == B_KING ||
                        board->getAbstractBoard()[static_cast<int>(boardPosition.x)][static_cast<int>(boardPosition.y)].id == W_KING)
                        ((King *)chosenPiece)->unsetCanCastle();

                    turn = !turn;
                }
                if (desiredPlace->id == DON_T_CARE)
                {
                    board->updatePosition(chosenPiece->getPosition(), boardPosition);
                    chosenPiece->setPosition(boardPosition);
                    turn = !turn;
                    if (kingCastle && board->getAbstractBoard()[static_cast<int>(boardPosition.x)][static_cast<int>(boardPosition.y)].id == currentKingID)
                    {
                        if (!((King *)chosenPiece)->getCanCastle())
                            goto end;
                        if (Vector2Equals(boardPosition, {0, 1}) || Vector2Equals(boardPosition, {7, 1})) // left castle
                        {
                            Piece *rook = currentSet->getPieceByPosition({boardPosition.x, 0});
                            board->updatePosition(rook->getPosition(), {boardPosition.x, 2});
                            rook->setPosition({boardPosition.x, 2});
                            ((King *)chosenPiece)->unsetCanCastle();
                        }
                        if (Vector2Equals(boardPosition, {0, 5}) || Vector2Equals(boardPosition, {7, 5})) // right castle
                        {
                            Piece *rook = currentSet->getPieceByPosition({boardPosition.x, 7});
                            board->updatePosition(rook->getPosition(), {boardPosition.x, 4});
                            rook->setPosition({boardPosition.x, 4});
                            ((King *)chosenPiece)->unsetCanCastle();
                        }
                    }
                    if (board->getAbstractBoard()[static_cast<int>(boardPosition.x)][static_cast<int>(boardPosition.y)].id == B_KING ||
                        board->getAbstractBoard()[static_cast<int>(boardPosition.x)][static_cast<int>(boardPosition.y)].id == W_KING)
                        ((King *)chosenPiece)->unsetCanCastle();
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

std::vector<Vector2> highlightAvailable(ChessBoard *board, Piece *piece)
{
    std::vector<Vector2> v;
    BoardPlace(*abstractBoard)[8] = board->getAbstractBoard();
    for (auto m : piece->getAllowedMoves())
    {
        Vector2 endPos = Vector2Add(piece->getPosition(), m);
        while (true)
        {
            if (!isInsideBoard(endPos))
                break;
            if (abstractBoard[static_cast<int>(endPos.x)][static_cast<int>(endPos.y)].id != PIECE::DON_T_CARE)
                break;
            v.push_back(endPos);
            DrawRectangle(endPos.y * SQUARE_SIZE, endPos.x * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE, HIGHLIGHT_AVAILABLE_EMPTY);
            if (abstractBoard[static_cast<int>(piece->getPosition().x)][static_cast<int>(piece->getPosition().y)].id == PIECE::B_KNIGHT ||
                abstractBoard[static_cast<int>(piece->getPosition().x)][static_cast<int>(piece->getPosition().y)].id == PIECE::W_KNIGHT)
                break;
            bool reachedMax = false;
            for (auto e : piece->getExtremeMoves())
                if (Vector2Equals(endPos, Vector2Add(e, piece->getPosition())))
                {
                    reachedMax = true;
                    break;
                }
            if (reachedMax)
                break;
            endPos = Vector2Add(endPos, m);
        }
    }
    return v;
}

std::vector<Vector2> highlightAttack(ChessBoard *board, Piece *piece)
{
    std::vector<Vector2> v;
    BoardPlace(*abstractBoard)[8] = board->getAbstractBoard();
    for (auto m : piece->getAttack())
    {
        Vector2 endPos = Vector2Add(piece->getPosition(), m);
        while (true)
        {
            if (!isInsideBoard(endPos))
                break;
            if (abstractBoard[static_cast<int>(endPos.x)][static_cast<int>(endPos.y)].id != PIECE::DON_T_CARE)
            {
                if (isOponent(&abstractBoard[static_cast<int>(endPos.x)][static_cast<int>(endPos.y)],
                              &abstractBoard[static_cast<int>(piece->getPosition().x)][static_cast<int>(piece->getPosition().y)]))
                {
                    v.push_back(endPos);
                    DrawRectangle(endPos.y * SQUARE_SIZE, endPos.x * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE, HIGHLIGHT_AVAILABLE_ATTACK);
                }
                break;
            }
            if (abstractBoard[static_cast<int>(piece->getPosition().x)][static_cast<int>(piece->getPosition().y)].id == PIECE::B_KNIGHT ||
                abstractBoard[static_cast<int>(piece->getPosition().x)][static_cast<int>(piece->getPosition().y)].id == PIECE::W_KNIGHT)
                break;
            bool reachedMax = false;
            for (auto e : piece->getExtremeMoves())
                if (Vector2Equals(endPos, Vector2Add(e, piece->getPosition())))
                {
                    reachedMax = true;
                    break;
                }
            if (reachedMax)
                break;
            endPos = Vector2Add(endPos, m);
        }
    }
    return v;
}

std::vector<Vector2> highlightSpecial(ChessBoard *board, Piece *piece)
{
    std::vector<Vector2> v;
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
        if (posX == 0 && posY == 3 && (abstractBoard[0][0].id == B_ROOK || abstractBoard[0][7].id == B_ROOK))
            enableSpecial = true;
        break;
    case PIECE::W_KING:
        if (posX == 7 && posY == 3 && (abstractBoard[7][0].id == W_ROOK || abstractBoard[7][7].id == W_ROOK))
            enableSpecial = true;
        break;
    default:
        break;
    }

    if (enableSpecial)
    {
        if (abstractBoard[posX][posY].id == B_PAWN || abstractBoard[posX][posY].id == W_PAWN)
            for (auto m : piece->getSpecial())
            {
                Vector2 newPos = Vector2Add(piece->getPosition(), m);
                posX = static_cast<int>(newPos.x);
                posY = static_cast<int>(newPos.y);
                if (abstractBoard[posX][posY].id != DON_T_CARE)
                {
                    v.clear();
                    enableSpecial = false;
                    break;
                }
                v.push_back(newPos);
            }
        if (abstractBoard[posX][posY].id == B_KING || abstractBoard[posX][posY].id == W_KING)
        {
            King *k = (King *)piece;
            if (k->getCanCastle())
            {
                for (int i = 1; i <= 2; i++) // castle to left
                {
                    Vector2 newPos = Vector2Add(k->getPosition(), {0, static_cast<float>(-i)});
                    if (abstractBoard[static_cast<int>(newPos.x)][static_cast<int>(newPos.y)].id != DON_T_CARE)
                    {
                        enableSpecial = false;
                        break;
                    }
                }
                if (enableSpecial)
                    v.push_back(Vector2Add(k->getPosition(), {0, -2}));
                enableSpecial = true;
                for (int i = 1; i <= 3; i++) // castle to right
                {
                    Vector2 newPos = Vector2Add(k->getPosition(), {0, static_cast<float>(i)});
                    if (abstractBoard[static_cast<int>(newPos.x)][static_cast<int>(newPos.y)].id != DON_T_CARE)
                    {
                        enableSpecial = false;
                        break;
                    }
                }
                if (enableSpecial)
                    v.push_back(Vector2Add(k->getPosition(), {0, 2}));
                if (v.size())
                    enableSpecial = true;
            }
        }
    }

    if (enableSpecial)
        for (auto m : v)
        {
            posX = static_cast<int>(m.x);
            posY = static_cast<int>(m.y);
            DrawRectangle(posY * SQUARE_SIZE, posX * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE, HIGHLIGHT_SPECIAL);
        }
    return v;
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