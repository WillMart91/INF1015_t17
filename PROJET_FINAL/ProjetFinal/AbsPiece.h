/*
* Author: Gabriel Sawka and Wiliam Martin
* Date: mai  6 2022
* Description: AbsPiece is the motherclass of every chess pieces in the game. It implements the aspect common to every pieces.
*/

#pragma once
#include <list>
#include "Square.h"

class AbsPiece
{
public:
	Square getSquare() { return position_; }
	void move(Square newPos);
	virtual std::list<Square> getValidMoves() = 0;

	bool isBlackTeam() { return blackTeam_; }
	AbsPiece(bool blackTeam, Square position,char pType,bool inStartPos=true);
	bool inStartPos() { return startPos_; }
	virtual ~AbsPiece() = default;
	bool isType(char t) { return t == pieceType_; }
private:
	bool blackTeam_;
	Square position_;
	bool startPos_;
	char pieceType_;
};


