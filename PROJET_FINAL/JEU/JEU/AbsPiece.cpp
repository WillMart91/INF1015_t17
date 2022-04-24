#include "AbsPiece.h"

AbsPiece::AbsPiece(bool blackTeam, Square position)
{
    blackTeam_ = blackTeam;
    position_ = position;
    hasMoved_ = false;
    alive_ = true;
}

