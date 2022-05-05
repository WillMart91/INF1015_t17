
#include "Rook.h"

Rook::Rook(bool blackTeam, Square position, bool inStartPos) : AbsPiece(blackTeam,position,'r', inStartPos)
{
}

std::list<Square> Rook::getValidMoves()
{
	std::list<std::pair<int, int>> allDirCopy = allDir;
	std::list<Square> p;
	Square pos = getSquare();
	int maxDist = std::max(std::max(pos.file, pos.rank), std::max(8 - pos.file, 8 - pos.rank));
	for (int d = 1; d <= maxDist; d++) {
		for (auto&& it = allDirCopy.begin(); it != allDirCopy.end(); it++)
		{
			Square checkPos = pos + *it * d;
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

	}

	return p;
}