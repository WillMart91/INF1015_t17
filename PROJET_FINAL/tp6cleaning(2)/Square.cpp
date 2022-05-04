/*author: Gabriel Sawka and Wiliam Martin
* date: 25 april
* description: implementation of custon operator for square struct (position on the board)
*/

#include "Square.h"
#include <vector>

	Square operator+(const Square p1, const Square p2)
	{
		return Square{ p1.file + p2.file, p1.rank + p2.rank };
	};

	Square operator+(const Square p1, const std::pair<int, int> move)
	{
		return Square{ p1.file + move.first,p1.rank + move.second };
	};


	std::pair<int, int> operator*(const std::pair<int, int> move, const int i)
	{
		return std::pair<int, int>{move.first * i, move.second * i};
	};

	std::pair<int, int> operator*(const int i, const std::pair<int, int> move)
	{
		return move * i;
	};



