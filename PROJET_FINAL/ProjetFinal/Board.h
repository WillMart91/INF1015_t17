#include "Square.h"
#include <vector>

class Board
{
public:
	Board();
	//vector of box
	bool squareOccupied(Square pos);
	void movePiece(ChessPiece piece, Square square);
private:
	std::vector < std::vector<Square>> chessBoard;


};

