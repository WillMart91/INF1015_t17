#include "Square.h"

Square operator+(const Square p1, const Square p2)
{
	return Square(p1.file +p2.file,p1.rank +p2.rank);
}
Square operator-(const Square p1, const Square p2)
{
	return Square(p1.file - p2.file, p1.rank - p2.rank);
}
