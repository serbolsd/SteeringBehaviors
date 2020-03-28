#pragma once
#include <CDVectors.h>
#include <SFML/Graphics.hpp>
using namespace CD;
class Wall
{
public:
	Wall();
	~Wall();
	void init(const CDVector2&_pos1, const CDVector2& _pos2);
	void render(sf::RenderWindow& _wind);
	CDVector2 getPos1() { return m_position1; };
	CDVector2 getWallVector() { return m_vectorWall; };
	CDVector2 getWallVectorRight() { return m_vectorRightWall; };
	float getAngle() { return m_angle; };
private:
	CDVector2 m_position1;
	CDVector2 m_position2;
	CDVector2 m_vectorWall;
	CDVector2 m_vectorRightWall;
	float calculateAngle(const CDVector2& _vec);
	sf::VertexArray m_line;
	float m_angle=0;
};