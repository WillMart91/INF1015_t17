#include "AbsPiece.h"


void AbsPiece::move(Square newPos)
{
    position_ = newPos;
    startPos_ = false;
}

AbsPiece::AbsPiece(bool blackTeam, Square position, char pType, bool inStartPos)
{
    blackTeam_ = blackTeam;
    position_ = position;
    startPos_ = inStartPos;
    pieceType_ = pType;
}
