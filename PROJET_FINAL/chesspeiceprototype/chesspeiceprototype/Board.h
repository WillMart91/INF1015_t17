#pragma once
#include <map>
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
private:
	Board()=default; 
	static Board* instance_;
	std::map<Square, AbsPiece*> chessBoard_;
	Square lastClicked_;
	bool blackTurn_;


	const std::list<std::pair<int, int>> knightCheck = { {2, 1},{-2, 1},{2, -1},{-2, -1},{1,2},{-1,2}, {1,-2},{-1,-2} };
	const std::list<std::pair<int, int>> bishopCheck = { {1, 1},{-1, 1},{1, -1},{-1, -1} };
	const std::list<std::pair<int, int>> rookCheck = { {1, 0},{-1, 0},{0, -1},{0, 1} };
	const std::list<std::pair<int, int>> pawnCheck = { {1, 1},{-1, 1} };
};

