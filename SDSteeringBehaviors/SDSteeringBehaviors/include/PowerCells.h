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
	void setPosition(const CDVector2& _pos) { m_position = _pos; m_cell.setPosition(_pos.x,_pos.y); };
	CDVector2 getPosition() { return m_position; };
	bool m_actived = true;
private:
	
	sf::CircleShape m_cell;
	float m_ratio = 5;
	CDVector2 m_position;
};