#include "AbsPiece.h"

bool AbsPiece::isAlive()
{
    return alive_;
}

AbsPiece::AbsPiece(bool blackTeam, Square position)
{
    blackTeam_ = blackTeam;
    position_ = position;
    hasMoved_ = false;
    alive_ = true;
}

Square AbsPiece::getPosition()
{
    return position_;
}
