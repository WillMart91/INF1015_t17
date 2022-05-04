/*author: Gabriel Sawka and Wiliam Martin
* date: 25 april
* description: implementation of a genreic piece
*/


#include "AbsPiece.h"

AbsPiece::AbsPiece(bool blackTeam, Square position)
{
    blackTeam_ = blackTeam;
    position_ = position;
    hasMoved_ = false;
    alive_ = true;
}

