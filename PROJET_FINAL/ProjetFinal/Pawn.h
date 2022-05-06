/*
* Author: Gabriel Sawka and Wiliam Martin
* Date: mai  6 2022
* Description: A pawn is the definition of a simple type of chess piece
*/

#include "Board.h"
class Pawn : public AbsPiece
{
public:
	Pawn(bool blackTeam, Square position, bool inStartPos = true);
	~Pawn() = default;
	virtual std::list<Square> getValidMoves();

private:
	const std::list<std::pair<int, int>> attMoves = { {1, 1},{-1, 1} };
	const std::pair<int, int> regMove = { 0, 1 };
	const std::pair<int, int> startMove = { 0, 2 };
};

