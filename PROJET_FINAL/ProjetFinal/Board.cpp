/*
* Author: Gabriel Sawka and Wiliam Martin
* Date: mai  6 2022
* Description: implementation of the class.
*/


#include "Board.h"
#include <algorithm>
Board* Board::instance_;
Square Board::lastClicked_ = { 9,9 };
bool Board::blackTurn_ = false;
std::vector<std::map<Square, AbsPiece*>> Board::layouts_ = std::vector<std::map<Square, AbsPiece*>>();
const std::list<std::pair<int, int>> Board::knightCheck_ = { {2, 1},{-2, 1},{2, -1},{-2, -1},{1,2},{-1,2}, {1,-2},{-1,-2} };
const std::list<std::pair<int, int>> Board::bishopCheck_ = { {1, 1},{-1, 1},{1, -1},{-1, -1} };
const std::list<std::pair<int, int>> Board::rookCheck_ = { {1, 0},{-1, 0},{0, -1},{0, 1} };
const std::list<std::pair<int, int>> Board::pawnCheck_ = { {1, 1},{-1, 1} };
std::map<Square, AbsPiece*> Board::chessBoard_ = std::map<Square, AbsPiece*>();
void Board::fillBoard(int layoutNumber)
{
	chessBoard_ = layouts_[layoutNumber];
	blackTurn_ = false;
}
Board::~Board()
{
	for (auto&& it = chessBoard_.begin(); it != chessBoard_.end(); it++) {
		delete it->second;
	}
}

std::list<Square> Board::getMovesOfPiece(Square clicked)
{
	std::list<Square> moves;

	lastClicked_ = clicked;
	if (chessBoard_[clicked] != nullptr) {
		if (chessBoard_[clicked]->isBlackTeam() == blackTurn_) {
			moves = chessBoard_[clicked]->getValidMoves();
		}
	}


	return moves;
}

std::list<std::pair<Square, Square>> Board::moveOnBoard(Square clicked)
{
	std::map<Square, AbsPiece*> chessBoardBefore = chessBoard_;
	std::list<Square> m = chessBoardBefore[lastClicked_]->getValidMoves();
	std::list<Square>::iterator it = std::find_if(m.begin(), m.end(), [&clicked](Square s) {return clicked == s; });

	chessBoard_[clicked] = chessBoard_[lastClicked_];
	chessBoard_.erase(lastClicked_);
	bool danger = false;
	for (auto&& it = chessBoard_.begin(); it != chessBoard_.end(); it++) {
		if (it->second != nullptr) {
			if (it->second->isBlackTeam() == blackTurn_ && it->second->isType('K')) {
				danger = validateMove(it->first);
				break;
			}
		}
	}
	std::list<std::pair<Square, Square>> moves;

	if (danger || it == m.end()) {
		moves.push_back({ lastClicked_, lastClicked_ });
		chessBoard_ = chessBoardBefore;
	}
	else {
		moves.push_back({ lastClicked_, clicked });
		chessBoard_[clicked]->move(clicked);
		blackTurn_ = !blackTurn_;
	}
	return moves;
}

bool Board::validateMove(Square endangeredPos)
{
	bool endanger = false;
	int maxDist = std::max(std::max(endangeredPos.file, endangeredPos.rank), std::max(8 - endangeredPos.file, 8 - endangeredPos.rank));
	std::list<std::pair<int, int>> knightCheckCopy = knightCheck_;
	for (auto&& it = knightCheckCopy.cbegin(); it != knightCheckCopy.cend(); it++)
	{
		Square checkPos = endangeredPos + *it;
		if (!Square::isValid(checkPos)) {
			continue;
		}
		AbsPiece* pieceOn = chessBoard_[checkPos];
		if (pieceOn != nullptr) {
			if (pieceOn->isType('k'))
			{
				if (pieceOn->isBlackTeam() != blackTurn_) {
					endanger=true;
				}
			}
		}
	}
	std::list<std::pair<int, int>> pawnCheckCopy = pawnCheck_;
	for (auto&& it = pawnCheckCopy.begin(); it != pawnCheckCopy.end(); it++)
	{
		Square checkPos = endangeredPos + *it * pow(-1, (int)!blackTurn_);
		if (!Square::isValid(checkPos)) {
			continue;
		}
		AbsPiece* pieceOn = chessBoard_[checkPos];
		if (pieceOn != nullptr) {
			if (pieceOn->isType('p'))
			{
				if (pieceOn->isBlackTeam() != blackTurn_) {
					endanger = true;
				}
			}
		}
	}
	std::list<std::pair<int, int>> bishopCheckCopy = bishopCheck_;
	std::list<std::list<std::pair<int, int>>::iterator> bIt;
	std::list<std::pair<int, int>> rookCheckCopy = rookCheck_;
	std::list<std::list<std::pair<int, int>>::iterator> rIt;
	for (int d = 1; d <= maxDist; d++) {
		for (auto&& it = bishopCheckCopy.begin(); it != bishopCheckCopy.end(); it++)
		{
			Square checkPos = endangeredPos + *it * d;
			if (!Square::isValid(checkPos)) {
				bIt.push_back(it);
				continue;
			}
			AbsPiece* pieceOn = chessBoard_[checkPos];
			if (pieceOn != nullptr) {
				if (pieceOn->isType('b') || pieceOn->isType('q'))
				{
					if (pieceOn->isBlackTeam() != blackTurn_) {
						endanger = true;
					}
					else {
						bIt.push_back(it);
					}
				}
				else {
					bIt.push_back(it);
				}
			}
		}
		int m = bIt.size();
		for (int i = 0; i < m; i++) {
			std::list<std::pair<int, int>>::iterator it = bIt.front();
			bishopCheckCopy.erase(it);
			bIt.pop_front();
		}
		for (auto&& it = rookCheckCopy.begin(); it != rookCheckCopy.end(); it++)
		{
			Square checkPos = endangeredPos + *it * d;
			if (!Square::isValid(checkPos)) {
				rIt.push_back(it);
				continue;
			}
			AbsPiece* pieceOn = chessBoard_[checkPos];
			if (pieceOn != nullptr) {
				if (pieceOn->isType('r') || pieceOn->isType('q'))
				{
					if (pieceOn->isBlackTeam() != blackTurn_) {
						endanger = true;
					}
					else {
						rIt.push_back(it);
					}
				}
				else {
					rIt.push_back(it);
				}
			}
		}
		int n = rIt.size();
		for (int i = 0; i < n; i++) {
			std::list<std::pair<int, int>>::iterator it = rIt.front();
			rookCheckCopy.erase(it);
			rIt.pop_front();
		}
	}
	return endanger;
}

std::map<Square, AbsPiece*> Board::getLayout(int layoutNumber)
{
	if (layoutNumber >= layouts_.size() || layoutNumber < 0) {
		return std::map<Square, AbsPiece*>();
	}
	else {
		fillBoard(layoutNumber);
		return layouts_[layoutNumber];
	}

}

