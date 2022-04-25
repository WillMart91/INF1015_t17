#pragma once


struct Position
{
public:
	int rank; 
	int file;
};
Position operator+(const Position p1, const Position p2);
Position operator-(const Position p1, const Position p2);
