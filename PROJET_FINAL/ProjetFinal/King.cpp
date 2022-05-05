#include "King.h"
#include <stdexcept>



int King::nbOfKings = 0;
King::King(bool blackTeam, Square position, bool inStartPos) :AbsPiece(blackTeam, position,'K', inStartPos)
{
	if (++nbOfKings > 2) {
		throw std::logic_error("king");
	}
}

King::~King()
{
	if (--nbOfKings == 1) {
		//throw std::logic_error("Win");
	}
}

std::list<Square> King::getValidMoves()
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
		if (pieceOn != nullptr) {
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
