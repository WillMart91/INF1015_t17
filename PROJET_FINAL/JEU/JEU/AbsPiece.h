#pragma once
#include "Square.h"
#include <vector>

class AbsPiece
{
public:
	virtual std::vector<Square> getValidPositions(const std::vector<std::vector<AbsPiece*>> chessBoard)=0;
	bool isAlive();
	Square getPosition() { return position_; }
	bool isBlackTeam() { return blackTeam_; }
	AbsPiece(bool blackTeam, Square position);
	bool inStartPos() { return !hasMoved_; }
private:
	bool blackTeam_;
	Square position_;
	bool hasMoved_;
	bool alive_;
};

