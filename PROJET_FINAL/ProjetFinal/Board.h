#pragma once
#include <map>

class Board
{
public:
	AbsPiece* getPieceOn(Square pos) { return chessBoard_[pos]; }
	static Board* getInstance() { return instance; }
	void fillBoard(std::map<Square, AbsPiece*> newBoard) { chessBoard_ = newBoard; }
	~Board();
	std::list<Square> getMovesOfPiece(Square clicked);
	std::list<std::pair<Square, Square>> moveOnBoard(Square clicked);
private:
	Board()=default; 
	static Board* instance;
	std::map<Square, AbsPiece*> chessBoard_;
	Square lastClicked;
	bool blackTurn;
};

