
#include "AbsPiece.h"
#include "Square.h"

AbsPiece::AbsPiece(bool blackTeam, Square position, bool inStartPos)
{
    blackTeam_ = blackTeam;
    position_ = position;
    startPos_ = inStartPos;
}
