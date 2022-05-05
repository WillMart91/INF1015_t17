#pragma once

struct Square
{
	int file; 
	int rank;
};
Square operator+(const Square p1, const Square p2);
Square operator-(const Square p1, const Square p2);
bool operator==(const Square p1, const Square p2);
