/*author: Gabriel Sawka and Wiliam Martin
* date: 25 april
* description: class declaring a generic piece
*/

#pragma once
#include "Square.h"
#include <vector>

class AbsPiece
{
public:
	virtual std::vector<Square> getValidPositions(const std::vector<std::vector<AbsPiece*>> chessBoard)=0;
	bool isAlive() { return alive_; }
	Square getPosition() { return position_; }
	bool isBlackTeam() { return blackTeam_; }
	AbsPiece(bool blackTeam, Square position);
	bool inStartPos() { return !hasMoved_; }
	virtual ~AbsPiece() = default;
private:
	bool blackTeam_;
	Square position_;
	bool hasMoved_;
	bool alive_;
};

