#include "raylib.h"
#include "raymath.h"
#include "ChessBoard.h"
#include <queue>

std::vector<Vector2> highlightAvailable(ChessBoard *board, Piece *piece);
std::vector<Vector2> highlightAttack(ChessBoard *board, Piece *piece);
std::vector<Vector2> highlightSpecial(ChessBoard *board, Piece *piece);
void removeOpponentsPiece(ChessBoard *board, Vector2 boardPosition, BoardPlace *desiredPlace, bool turn);
std::vector<Vector2> Lee(BoardPlace (*abstractBoard)[8], Vector2 start, Vector2 end, std::vector<Vector2> allowedMoves);

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
        // ChessSet *opposingSet = (turn) ? board->getWhiteSet() : board->getBlackSet();
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
                goToSpots.clear();
                goToSpots = highlightAvailable(board, chosenPiece);
                VectorAppend(goToSpots, highlightAttack(board, chosenPiece));
                VectorAppend(goToSpots, highlightSpecial(board, chosenPiece));
            }
        }
        if (pieceSelected && IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        {
            if (!Vector2Equals(boardPosition, chosenPiece->getPosition()) && find(goToSpots, boardPosition))
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
    //     bool enableSpecial = false;
    //     int posX = static_cast<int>(piece->getPosition().x);
    //     int posY = static_cast<int>(piece->getPosition().y);
    //     BoardPlace(*abstractBoard)[8] = board->getAbstractBoard();
    //     switch (abstractBoard[posX][posY].id)
    //     {
    //     case PIECE::B_PAWN:
    //         if (posX == 1)
    //             enableSpecial = true;
    //         break;
    //     case PIECE::W_PAWN:
    //         if (posX == 6)
    //             enableSpecial = true;
    //         break;
    //     case PIECE::B_KING:
    //         if (posX == 0 && posY == 3)
    //             enableSpecial = true;
    //         break;
    //     case PIECE::W_KING:
    //         if (posX == 7 && posY == 3)
    //             enableSpecial = true;
    //         break;
    //     default:
    //         break;
    //     }
    //     if (enableSpecial)
    //         for (auto m : piece->getSpecial())
    //         {
    //             Vector2 newPos = Vector2Add(piece->getPosition(), m);
    //             posX = static_cast<int>(newPos.x);
    //             posY = static_cast<int>(newPos.y);
    //             if (abstractBoard[posX][posY].id != DON_T_CARE)
    //             {
    //                 enableSpecial = false;
    //                 break;
    //             }
    // }

    //     if (enableSpecial)
    //         for (auto m : piece->getSpecial())
    //         {
    //             Vector2 newPos = Vector2Add(piece->getPosition(), m);
    //             posX = static_cast<int>(newPos.x);
    //             posY = static_cast<int>(newPos.y);
    //             DrawRectangle(posY * SQUARE_SIZE, posX * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE, HIGHLIGHT_SPECIAL);
    //         }
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

std::vector<Vector2> Lee(BoardPlace (*abstractBoard)[8], Vector2 start, Vector2 end, std::vector<Vector2> allowedMoves)
{
    std::vector<Vector2> v;
    std::queue<Vector2> q;
    bool taken[8][8];
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            taken[i][j] = false;
    q.push(start);
    while (!q.empty())
    {
        Vector2 currPos = q.front();
        taken[static_cast<int>(currPos.x)][static_cast<int>(currPos.y)] = true;
        q.pop();
        for (auto m : allowedMoves)
        {
            Vector2 nextPos = Vector2Add(currPos, m);
            int posX = static_cast<int>(nextPos.x);
            int posY = static_cast<int>(nextPos.y);
            if (isInsideBoard(nextPos) && !taken[posX][posY] && abstractBoard[posX][posY].id == PIECE::DON_T_CARE)
            {
                q.push(nextPos);
                v.push_back(nextPos);
                if (Vector2Equals(nextPos, end))
                    return v;
            }
        }
    }
    return v;
}
