/*
* Author: Gabriel Sawka and Wiliam Martin
* Date: mai  6 2022
* Description: implementation of the class.
*/
#include "Bishop.h"

Bishop::Bishop(bool blackTeam, Square position, bool inStartPos) :AbsPiece(blackTeam, position,'b', inStartPos)
{
}

std::list<Square> Bishop::getValidMoves()
{
	std::list<std::pair<int, int>> allDirCopy = allDir;
	std::list<Square> p = std::list<Square>();
	Square pos = getSquare();
	std::list<std::list<std::pair<int, int>>::iterator> iterator;
	int maxDist = std::max(std::max(pos.file, pos.rank), std::max(8 - pos.file, 8 - pos.rank));
	for (int d = 1; d <= maxDist; d++) {
		for (auto&& it = allDirCopy.begin(); it != allDirCopy.end(); it++)
		{
			Square checkPos = pos + *it * d;
			if (!Square::isValid(checkPos)) {
				iterator.emplace_back(it);
				continue;
			}
			AbsPiece* pieceOn = Board::getInstance()->getPieceOn(checkPos);
			if (pieceOn != nullptr) {
				if (pieceOn->isBlackTeam() != ((AbsPiece*)this)->isBlackTeam()) {
					p.push_back(checkPos);
				}
				iterator.emplace_back(it);
			}
			else {
				p.push_back(checkPos);
			}
		}
		int m = iterator.size();
		for (int i = 0; i < m; i++) {
			std::list<std::pair<int, int>>::iterator l = iterator.front();
			allDirCopy.erase(l);
			iterator.pop_front();
		}
	}

	return p;
}
