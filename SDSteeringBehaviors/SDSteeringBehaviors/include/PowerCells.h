#pragma once
#include <CDVectors.h>
#include <SFML/Graphics.hpp>
using namespace CD;
class PowerCells
{
public:
	PowerCells();
	~PowerCells();
	void init(const CDVector2& _position);
	void render(sf::RenderWindow& _wind);
	bool m_actived = true;
private:
	
	sf::CircleShape m_cell;
	float m_ratio = 5;
	CDVector2 m_position;
};