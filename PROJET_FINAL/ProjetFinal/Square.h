#include "ChessPiece.h"

class Position;

class Square
{

public:
	Square(int rank, int file);
	~Square()=default;
	void moveAway() { pieceOnMe = nullptr; }
	void moveToMe(ChessPiece* piece) { pieceOnMe = piece; }
	bool imOccupied() { return pieceOnMe != nullptr; }
	bool friendlyOccupied(ChessPiece* piece);
	Position getPosition() { return position; }
private:
	Position position;
	ChessPiece* pieceOnMe;
};

