#pragma once
#include <vector>

	struct Square
	{
		int file;
		int rank;
	};
	Square operator+(const Square p1, const Square p2);
	Square operator+(const Square p1, const std::pair<int, int> move);
	std::pair<int, int> operator*(const std::pair<int, int> move, const int i);
	std::pair<int, int> operator*(const int i, const std::pair<int, int> move);



