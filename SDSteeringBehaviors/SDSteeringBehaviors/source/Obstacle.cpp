#include "Obstacle.h"
void Obstacle::Init(ObstacleDescriptor _Desc)
{
	myDesc = _Desc;
	shape.setRadius(myDesc.ratio);
	shape.setOrigin(myDesc.ratio, myDesc.ratio);
	shape.setPosition(myDesc.position.x, myDesc.position.y);
	shape.setFillColor(myDesc.shapeColor);
}

void Obstacle::Render(sf::RenderWindow& _wind)
{
	_wind.draw(shape);
}
