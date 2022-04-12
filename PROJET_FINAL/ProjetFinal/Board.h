#include "Square.h"
#include <vector>

class Board
{
public:
	Board();
	//vector of box
	bool squareOccupied(Position pos);
	void movePiece(ChessPiece piece, Position square);
private:
	std::vector < std::vector<Square>> chessBoard;


};

