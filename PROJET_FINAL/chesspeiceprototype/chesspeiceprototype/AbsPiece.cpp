#include "AbsPiece.h"


AbsPiece::AbsPiece(bool blackTeam, Square position, char pType, bool inStartPos)
{
    blackTeam_ = blackTeam;
    position_ = position;
    startPos_ = inStartPos;
    pieceType_ = pType;
}
