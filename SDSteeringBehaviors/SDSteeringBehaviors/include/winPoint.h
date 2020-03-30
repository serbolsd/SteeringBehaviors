#pragma once
#include <CDVectors.h>
#include <SFML/Graphics.hpp>
using namespace CD;
class WinPoint
{
public:
	WinPoint();
	~WinPoint();
	bool m_bIsActived = false;
	void init();
	void render(sf::RenderWindow& _wind);
	void setPosition(const float& posx, const float& posy);
	CDVector2 getPosition() { return m_position; };
	float getRatio() { return m_ratio; };
private:
	CDVector2 m_position;
	sf::CircleShape m_shape;
	float m_ratio = 15;
	sf::Color m_colorDesactive = {0,100,100,100};
	sf::Color m_colorActivated = sf::Color::Cyan;
};