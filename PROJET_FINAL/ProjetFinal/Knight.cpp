#include "Knight.h"

#include "AbsPiece.h"
#include "Board.h"
#include "Square.h"


Knight::Knight(bool blackTeam, Square position, bool inStartPos) :AbsPiece(blackTeam,position,inStartPos)
{
}

std::list<Square> Knight::getValidMoves()
{
	std::list<Square> p;
	Square pos = getSquare();

	for (auto&& it = allMoves.begin(); it != allMoves.end(); it++) 
	{
		Square checkPos = pos + *it;
		if (Square::isValid(checkPos)) {
			continue;
		}
		AbsPiece* pieceOn = Board::getInstance()->getPieceOn(checkPos);
		if ( pieceOn != nullptr) {
			if (pieceOn->isBlackTeam() != isBlackTeam()) {
				p.push_back(checkPos);
			}
		}
		else {
			p.push_back(checkPos);
		}
	}
	return p;
}