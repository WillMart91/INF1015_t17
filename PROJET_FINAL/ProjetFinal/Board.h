#pragma once
#include <map>
#include <list>
#include "AbsPiece.h"
class Board
{
public:
	AbsPiece* getPieceOn(Square pos) { return chessBoard_[pos]; }
	static Board* getInstance() { return instance_; }
	void fillBoard(std::map<Square, AbsPiece*> newBoard) { chessBoard_ = newBoard; }
	~Board();
	std::list<Square> getMovesOfPiece(Square clicked);
	std::list<std::pair<Square, Square>> moveOnBoard(Square clicked);
	bool validateMove(Square endangeredPos);
	Square getLastClicked() { return lastClicked_; }
	void setLastClicked(Square newClick) { lastClicked_ = newClick; }
private:
	Board()=default; 
	static Board* instance_;
	static std::map<Square, AbsPiece*> chessBoard_;
	static Square lastClicked_;
	static bool blackTurn_;


	static const std::list<std::pair<int, int>> knightCheck_; 
	static const std::list<std::pair<int, int>> bishopCheck_; 
	static const std::list<std::pair<int, int>> rookCheck_;
	static const std::list<std::pair<int, int>> pawnCheck_;
};

