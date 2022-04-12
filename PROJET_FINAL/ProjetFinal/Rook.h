#include "ChessPiece.h"
class Rook :public ChessPiece
{
public:
    Rook(bool isBlackTeam, QGraphicsItem* parent = 0);

    void setImage(bool isBlackTeam);
    std::vector<Position> calculateMoves();

};