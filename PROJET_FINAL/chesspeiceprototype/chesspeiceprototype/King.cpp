#include "AbsPiece.h"
#include "Board.h"

#include "Bishop.h"
#include "Knight.h"
#include "Pawn.h"
#include "Queen.h"
#include "Rook.h"
#include <stdexcept>
#include "King.h"


King::King(bool blackTeam, Square position, bool inStartPos) :AbsPiece(blackTeam, position, inStartPos)
{
	if (++nbOfKings >= 2) {
		throw std::logic_error("king");
	}
}

King::~King()
{
	if (--nbOfKings == 1) {
		throw std::logic_error("Win");
	}
}

std::list<Square> King::getValidMoves()
{
	std::list<std::pair<int, int>> allDirCopy = allMoves;
	std::list<Square> p;
	Square pos = getSquare();
	int maxDist = std::max(std::max(pos.file, pos.rank), std::max(8 - pos.file, 8 - pos.rank));

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


bool King::isChecked()
{
	Square pos = getSquare();
	int maxDist = std::max(std::max(pos.file, pos.rank), std::max(8 - pos.file, 8 - pos.rank));
	for (auto&& it = knightCheck.begin(); it != knightCheck.end(); it++)
	{
		Square checkPos = pos + *it;
		if (Square::isValid(checkPos)) {
			continue;
		}
		AbsPiece* pieceOn = Board::getInstance()->getPieceOn(checkPos);
		if (dynamic_cast<Knight*>(pieceOn) != NULL)
		{
			if (pieceOn->isBlackTeam() != isBlackTeam()) {
				return true;
			}
		}
	}
	for (auto&& it = pawnCheck.begin(); it != pawnCheck.end(); it++)
	{
		Square checkPos = pos + *it * ((-1) ^ (int)isBlackTeam());
		if (Square::isValid(checkPos)) {
			continue; 
		}
		AbsPiece* pieceOn = Board::getInstance()->getPieceOn(checkPos);
		if (dynamic_cast<Pawn*>(pieceOn) != NULL)
		{
			if (pieceOn->isBlackTeam() != isBlackTeam()) {
				return true; 
			}
		}
	}
	std::list<std::pair<int, int>> bishopCheckCopy = bishopCheck;
	std::list<std::pair<int, int>> rookCheckCopy = rookCheck;
	for (int d = 1; d <= maxDist; d++) {
		for (auto&& it = bishopCheckCopy.begin(); it != bishopCheckCopy.end(); it++)
		{
			Square checkPos = pos + *it;
			if (Square::isValid(checkPos)) {
				bishopCheckCopy.erase(it);
				continue;
			}
			AbsPiece* pieceOn = Board::getInstance()->getPieceOn(checkPos);
			if (pieceOn != nullptr) {
				if (dynamic_cast<Bishop*>(pieceOn) != NULL || dynamic_cast<Queen*>(pieceOn) != NULL)
				{
					if (pieceOn->isBlackTeam() != isBlackTeam()) {
						return true;
					}
					else {
						bishopCheckCopy.erase(it);
					}
				}
				else {
					bishopCheckCopy.erase(it);
				}
			}
		}
		for (auto&& it = rookCheckCopy.begin(); it != rookCheckCopy.end(); it++)
		{
			Square checkPos = pos + *it;
			if (Square::isValid(checkPos)) {
				rookCheckCopy.erase(it);
				continue;
			}
			AbsPiece* pieceOn = Board::getInstance()->getPieceOn(checkPos);
			if (pieceOn != nullptr) {
				if (dynamic_cast<Rook*>(pieceOn) != NULL || dynamic_cast<Queen*>(pieceOn) != NULL)
				{
					if (pieceOn->isBlackTeam() != isBlackTeam()) {
						return true;
					}
					else {
						rookCheckCopy.erase(it);
					}
				}
				else {
					rookCheckCopy.erase(it);
				}
			}
		}
	}
	return false;
}
