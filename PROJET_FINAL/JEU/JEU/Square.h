#pragma once
#include <vector>

	struct Square
	{
		int file;
		int rank;
	};
	Square operator+(const Square p1, const Square p2);
	Square operator+(const Square p1, const std::vector<int, int> move);
	std::vector<int, int> operator*(const std::vector<int, int> move, const int i);
	std::vector<int, int> operator*(const int i, const std::vector<int, int> move);



