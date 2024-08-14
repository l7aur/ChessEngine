#include "ChessBoard.h"

ChessBoard::ChessBoard(float size)
{
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
        {
            board[i][j].rectangle.x = i * SQUARE_SIZE;
            board[i][j].rectangle.y = j * SQUARE_SIZE;
            board[i][j].rectangle.width = board[i][j].rectangle.height = SQUARE_SIZE;
            board[i][j].rectangleColor = (i + j) % 2;
        }
    this->whiteSet = new ChessSet(PLAYER_COLORS::WHITE_PLAYER);
    this->blackSet = new ChessSet(PLAYER_COLORS::BLACK_PLAYER);
    setBoardIds();
}

void ChessBoard::setBoardIds()
{
    board[0][3].id = B_KING;
    board[0][4].id = B_QUEEN;
    board[0][0].id = board[0][7].id = B_ROOK;
    board[0][1].id = board[0][6].id = B_KNIGHT;
    board[0][2].id = board[0][5].id = B_BISHOP;
    for (int i = 0; i < 8; i++)
        board[1][i].id = B_PAWN;
    board[7][3].id = W_KING;
    board[7][4].id = W_QUEEN;
    board[7][0].id = board[7][7].id = W_ROOK;
    board[7][1].id = board[7][6].id = W_KNIGHT;
    board[7][2].id = board[7][5].id = W_BISHOP;
    for (int i = 0; i < 8; i++)
        board[6][i].id = W_PAWN;
}

void ChessBoard::draw(Color firstColor, Color secondColor) const
{
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
        {
            Color color = (board[i][j].rectangleColor == 0) ? firstColor : secondColor;
            DrawRectangle(board[i][j].rectangle.x, board[i][j].rectangle.y, board[i][j].rectangle.width, board[i][j].rectangle.height, color);
        }
    this->whiteSet->draw();
    this->blackSet->draw();
}

bool ChessBoard::isInside(int i, int j) const
{
    if (i < 0 || j < 0 || i > 7 || j > 7)
        return false;
    return true;
}

void ChessBoard::updatePosition(Vector2 oldPos, Vector2 newPos)
{
    std::swap(this->board[static_cast<int>(oldPos.x)][static_cast<int>(oldPos.y)].id,
              this->board[static_cast<int>(newPos.x)][static_cast<int>(newPos.y)].id);
}

BoardPlace ChessBoard::at(int i, int j) const
{
    i = (i > 7) ? 7 : i;
    i = (i < 0) ? 0 : i;
    j = (j > 7) ? 7 : j;
    j = (j < 0) ? 0 : j;
    return this->board[i][j];
}

void ChessBoard::printState() const
{
    std::cout << "START BOARD\n";
    for (int i = 0; i < 8; i++, std::cout << '\n')
        for (int j = 0; j < 8; j++, std::cout << std::setw(9))
        {
            std::string name = (this->board[i][j].id == B_KING)     ? "B_KING"
                               : (this->board[i][j].id == B_QUEEN)  ? "B_QUEEN"
                               : (this->board[i][j].id == B_ROOK)   ? "B_ROOK"
                               : (this->board[i][j].id == B_KNIGHT) ? "B_KNIGHT"
                               : (this->board[i][j].id == B_BISHOP) ? "B_BISHOP"
                               : (this->board[i][j].id == B_PAWN)   ? "B_PAWN"
                               : (this->board[i][j].id == W_KING)   ? "W_KING"
                               : (this->board[i][j].id == W_QUEEN)  ? "W_QUEEN"
                               : (this->board[i][j].id == W_ROOK)   ? "W_ROOK"
                               : (this->board[i][j].id == W_KNIGHT) ? "W_KNIGHT"
                               : (this->board[i][j].id == W_BISHOP) ? "W_BISHOP"
                               : (this->board[i][j].id == W_PAWN)   ? "W_PAWN"
                                                                    : "????????";
            std::cout << name << ' ';
        }
    std::cout << "END BOARD\n";
}

ChessBoard::~ChessBoard()
{
    delete this->whiteSet;
    delete this->blackSet;
}
