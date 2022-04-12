#pragma once
#include "ChessPiece.h"

class Bishop:ChessPiece
{
public:
	Bishop();
	~Bishop();

	virtual void calculateMoves(Board* board);
	//std::vector<Position> getPossibleMoves() { return movesList };
private:
	std::vector<Position> movesList;
	const int RANGE = 8;
	Position position;
	const std::vector<std::vector<int, int>> direction = { {1,-1} , {1, 1}, {-1, 1}, {-1, -1} }; 
};

