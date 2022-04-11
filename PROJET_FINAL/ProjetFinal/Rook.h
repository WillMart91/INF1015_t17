#include "ChessPiece.h"
class Rook :public ChessPiece
{
public:
    Rook(bool blackTeam, QGraphicsItem* parent = 0);

    void setImage();
    std::vector<Position> calculateMoves();

};