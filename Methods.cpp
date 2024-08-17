#include "Methods.h"
#include "raymath.h"

std::vector<Vector2> getAvailable(ChessBoard *board, Piece *piece)
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

void highlight(std::vector<Vector2> v, Color c)
{
    for (auto endPos : v)
        DrawRectangle(endPos.y * SQUARE_SIZE, endPos.x * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE, c);
}

bool getCheckState(ChessBoard *board, ChessSet *opposingSet, King *king)
{
    for (auto p : opposingSet->getPiecesOnBoard())
    {
        std::vector<Vector2> v = getAttack(board, p);
        for (auto m : v)
            if (Vector2Equals(m, king->getPosition()))
                return true;
        v.clear();
    }
    return false;
}

std::vector<Vector2> getAttack(ChessBoard *board, Piece *piece)
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

std::vector<Vector2> getSpecial(ChessBoard *board, Piece *piece)
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
    return v;
}

void removeOpponentsPiece(ChessSet *opposingSet, Vector2 boardPosition, BoardPlace *desiredPlace)
{
    desiredPlace->id = DON_T_CARE;
    std::vector<Piece *> &pieces = opposingSet->getPiecesOnBoard();

    for (auto p = pieces.begin(); p != pieces.end(); p++)
        if (Vector2Equals((*p)->getPosition(), boardPosition))
        {
            pieces.erase(p);
            break;
        }
}