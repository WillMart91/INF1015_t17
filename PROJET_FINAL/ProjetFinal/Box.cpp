#include "Box.h"


Box::Box(int posX, int posY, int sizeX, int sizeY, QBrush color, float opacity)
{
	int _posX = posX;
	int _posY = posY;
	int _sizeX = sizeX;
	int _sizeY = sizeY;
	QBrush _color = color;
	float _opacity = opacity;

	createVisual();
}

void Box::createVisual()
{
	QGraphicsRectItem* rect = new QGraphicsRectItem();
	rect->setRect(_posX, _posY, _sizeX, _sizeY);
	rect->setBrush(_color);
	rect->setOpacity(_opacity);
	scene->addItem(rect);
}