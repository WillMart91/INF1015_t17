/*
* Author: Gabriel Sawka and Wiliam Martin
* Date: mai  6 2022
* Description: implementation of the class.
*/
#include "Knight.h"


Knight::Knight(bool blackTeam, Square position, bool inStartPos) :AbsPiece(blackTeam,position,'k', inStartPos)
{
}

std::list<Square> Knight::getValidMoves()
{
	std::list<Square> p = std::list<Square>();
	Square pos = getSquare();

	for (auto&& it = allMoves.begin(); it != allMoves.end(); it++) 
	{
		Square checkPos = pos + *it;
		if (!Square::isValid(checkPos)) {
			continue;
		}
		AbsPiece* pieceOn = Board::getInstance()->getPieceOn(checkPos);
		if ( pieceOn != nullptr) {
			if (pieceOn->isBlackTeam() != ((AbsPiece*)this)->isBlackTeam()) {
				p.push_back(checkPos);
			}
		}
		else {
			p.push_back(checkPos);
		}
	}
	return p;
}