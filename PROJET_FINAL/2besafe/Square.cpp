#include "Square.h"

Square operator+(const Square p1, const Square p2)
{
	return Square(p1.rank+p2.rank,p1.file+p2.file);
}
Square operator-(const Square p1, const Square p2)
{
	return Square(p1.rank - p2.rank, p1.file - p2.file);
}
