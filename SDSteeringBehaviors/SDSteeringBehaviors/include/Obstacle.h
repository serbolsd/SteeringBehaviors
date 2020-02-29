#pragma once
#include <CDVectors.h>
#include "SFML/Graphics.hpp"
struct ObstacleDescriptor
{
	float ratio = 0;
	CD::CDVector2 position = {0,0};
	sf::Color shapeColor = { 130,0,255,255 };
};

class Obstacle
{
public:
	Obstacle() {};
	~Obstacle() {};
	float getRatio() { return myDesc.ratio; };
	CD::CDVector2 getPosition() { return myDesc.position; };
	void Init(ObstacleDescriptor _Desc);
	void Update() {};
	void Render(sf::RenderWindow& _wind);
	void Delete() {};
private:
	ObstacleDescriptor myDesc;
	sf::CircleShape shape;
};