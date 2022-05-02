#include "King.h"
#include <iostream>
#include <stdexcept>
int King::nbOfKings=0;
King::King(bool blackTeam, Square beginPos) :AbsPiece(blackTeam, beginPos)
{
	if (++nbOfKings > 2) {
		std::cout << "The maximum number of Kings is already on the board!";
		throw std::logic_error("king");
	}
}

std::vector<Square> King::getValidPositions(const std::vector<std::vector<AbsPiece*>> chessBoard)
{
	Square pos = getPosition();
	std::vector<Square> moves;
	for (int i = 0; i < direction.size(); i++)
	{
		if (chessBoard[pos.file + direction[i].first * range][pos.rank + direction[i].second * range] != nullptr) {
			if (chessBoard[pos.file + direction[i].first * range][pos.rank + direction[i].second * range]->isBlackTeam() != this->isBlackTeam()) {
				moves.push_back(pos + direction[i] * range);
			}
		}
		else {
			moves.push_back(pos + direction[i] * range);
		}

	}
	return moves;

}

bool King::isChecked(const std::vector<std::vector<AbsPiece*>> chessBoard)
{
	std::vector<std::pair<int, int>> dir = direction;
	for (int r = 1; r < 8; r++) {
		for (int d = 0; d < dir.size(); d++) {
			//if ()
		}
	}
	return false;
}

King::~King()
{
	nbOfKings--;
	//va pt crash si lattribut est delete avant, sinon faire throw king dead et que le board catch et verif la color de lautre king pour declarer le winner
	if (nbOfKings == 1) {
		if (isBlackTeam()) {
			std::cout << "Black win";
		}
		else {
			std::cout << "White win";
		}
	}

}
