#pragma once

#include "Game.h"


class Box : Game
{
	//Q_OBJECT
	
public:
	Box(int posX, int posY, int sizeX, int sizeY, QBrush color, float opacity);
	// ~Box();
	void createVisual();

	int _posX;
	int _posY;
	int _sizeX;
	int _sizeY;
	QBrush _color;
	float _opacity;

};

