#pragma once
#include <vector>
#include <CDVectors.h>
#include <SFML/Graphics.hpp>
using namespace CD;
class Boid;
class Laser
{
public:
	Laser();
	~Laser();
	void init(const CDVector2& _pos1,const CDVector2& _pos2,float*_deltaTime);
	void update(std::vector<Boid*> _boid, Boid* _player);
	void render(sf::RenderWindow& _wind);
	CDVector2 getPos1() { return m_pos1; };
	CDVector2 getPos2() { return m_pos2; };
	float* m_pDeltaTime=nullptr;
private:
	void waitForPlayer(Boid*_player);
	void checkBoids(std::vector<Boid*> _boid);
	float m_elapseTime=0;
	float m_timeActivate=4;
	const float m_constTimeActivate=3;
	float m_timeToActivate=0.06;
	const float m_constTimeToActivate = 0.1;
	bool m_isActivated = false;
	bool m_isGoingToActivated = false;
	float m_ratio=5;
	CDVector2 m_pos1;
	CDVector2 m_pos2;
	CDVector2 m_sizeToPos1;
	CDVector2 m_sizeToPos2;
	float m_length = 0;
	sf::Color m_colorDesactivated = {255,0,0,100};
	sf::Color m_colorActivated = { 255,0,0,255 };
	sf::VertexArray line;
	sf::ConvexShape line2;
	sf::RectangleShape lin;
	float calculateAngle(const CDVector2& _vec);
};