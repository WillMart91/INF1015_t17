#include "King.h"
#include <stdexcept>




King::King(bool blackTeam, Square position, bool inStartPos) :AbsPiece(blackTeam, position,'K', inStartPos)
{
	if (++nbOfKings >= 2) {
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
	std::list<std::pair<int, int>> allDirCopy = allMoves;
	std::list<Square> p;
	Square pos = getSquare();
	for (auto&& it = allDirCopy.begin(); it != allDirCopy.end(); it++)
	{
		Square checkPos = pos + *it;
		if (Square::isValid(checkPos)) {
			allDirCopy.erase(it);
			continue;
		}
		AbsPiece* pieceOn = Board::getInstance()->getPieceOn(checkPos);
		if (pieceOn != nullptr) {
			if (pieceOn->isBlackTeam() != isBlackTeam()) {
				p.push_back(checkPos);
			}
			allDirCopy.erase(it);
		}
		else {
			p.push_back(checkPos);
		}
	}


	return p;
}
