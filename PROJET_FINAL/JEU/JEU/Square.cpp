#include "Square.h"
#include <vector>

	Square operator+(const Square p1, const Square p2)
	{
		return Square{ p1.file + p2.file, p1.rank + p2.rank };
	};

	Square operator+(const Square p1, const std::vector<int, int> move)
	{
		return Square{ p1.file + move[0],p1.rank + move[1] };
	};


	std::vector<int, int> operator*(const std::vector<int, int> move, const int i)
	{
		return std::vector<int, int>{move[0] * i, move[1] * i};
	};

	std::vector<int, int> operator*(const int i, const std::vector<int, int> move)
	{
		return move * i;
	};



