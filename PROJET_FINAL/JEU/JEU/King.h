#pragma once

#include "AbsPiece.h"
class King :AbsPiece
{
public:
	King(bool blackTeam, Square beginPos);
	virtual std::vector<Square> getValidPositions(const std::vector<std::vector<AbsPiece*>> chessBoard);
	bool isChecked(const std::vector<std::vector<AbsPiece*>> chessBoard);
	~King();
	//AbsPiece* castle();
private:
	static int nbOfKings;

	const int range = 1;
	const std::vector<std::vector<int, int>> direction = { {1, 0}, {1,1}, {0,1}, {-1,1}, {-1,0}, {-1,-1}, {0,-1}, {1,-1} };
	const std::vector<std::vector<int, int>> rookDir = { {1, 0}, {0,1}, {-1,0}, {0,-1}};
	const std::vector<std::vector<int, int>> bishopDir = { {1,1}, {-1,1},{-1,-1}, {1,-1} };
	const std::vector<std::vector<int, int>> knightDir = { {2, 1}, {2,-1}, {-2,1}, {-2,-1}, {1,2}, {1,-2}, {-1,2}, {-1,-2} };
};

