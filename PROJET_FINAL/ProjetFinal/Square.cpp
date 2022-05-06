/*
* Author: Gabriel Sawka and Wiliam Martin
* Date: mai  6 2022
* Description: implementation of the class.
*/
#include "Square.h"
#include <vector>

Square operator+(const Square p1, const Square p2)
{
	return Square{ p1.file + p2.file, p1.rank + p2.rank };
}

Square operator+(const Square p1, const std::pair<int, int> move)
{
	return Square{ p1.file + move.first,p1.rank + move.second };
}
Square operator+(const std::pair<int, int> move, const Square p1)
{
	return p1 + move;
}


std::pair<int, int> operator*(const std::pair<int, int> move, const int i)
{
	return std::pair<int, int>{move.first* i, move.second* i};
}

std::pair<int, int> operator*(const int i, const std::pair<int, int> move)
{
	return move * i;
}
bool operator==(const Square p1, const Square p2)
{
	return p1.file == p2.file && p1.rank == p2.rank;
}

bool operator<(const Square p1, const Square p2)
{
	return p1.file < p2.file || (p1.file == p2.file && p1.rank < p2.rank);
}

bool Square::isValid(Square s)
{
	return (s.file >= 1 && s.file <= 8) && (s.rank >= 1 && s.rank <= 8);
}

