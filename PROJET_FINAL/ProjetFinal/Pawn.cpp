/*
* Author: Gabriel Sawka and Wiliam Martin
* Date: mai  6 2022
* Description: implementation of the class.
*/

#include "Pawn.h"

Pawn::Pawn(bool blackTeam, Square position, bool inStartPos) : AbsPiece(blackTeam, position, 'p', inStartPos)
{
}

std::list<Square> Pawn::getValidMoves()
{
	std::list<Square> p = std::list<Square>();
	Square pos = getSquare();
	int side =(int)isBlackTeam();
	side = pow(-1, side);
	Square checkPos = (regMove * side) + pos;
	AbsPiece* pieceOn = Board::getInstance()->getPieceOn(checkPos);
	if (Square::isValid(checkPos) && pieceOn == nullptr)
	{
		p.push_back(checkPos);
	}
	checkPos = (startMove * side) + pos;
	pieceOn = Board::getInstance()->getPieceOn(checkPos);
	if (Square::isValid(checkPos) && inStartPos() && pieceOn == nullptr)
	{
		p.push_back(checkPos);
	}
	for (auto&& it = attMoves.begin(); it != attMoves.end(); it++) {
		checkPos = (*it * side) + pos;
		pieceOn = Board::getInstance()->getPieceOn(checkPos);
		if (pieceOn != nullptr) {
			if (Square::isValid(checkPos) && (pieceOn->isBlackTeam() != ((AbsPiece*)this)->isBlackTeam()))
			{
				p.push_back(checkPos);
			}
		}
		
	}
	return p;
}
