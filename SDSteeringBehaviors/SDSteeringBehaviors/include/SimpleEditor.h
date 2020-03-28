#pragma once
#include <CDVectors.h>
#include <SFML/Graphics.hpp>
#include <Boid.h>
#include <Obstacle.h>
#include <Wall.h>
#include <PowerCells.h>
#include <Laser.h>
#include <vector>
using namespace std;
class SimpleEditor
{
public:
	SimpleEditor();
	~SimpleEditor();
	void Init(const float& windlength, const float& windWidth, float* _deltaTime);
	void Update();
	void render(sf::RenderWindow& _wind);
	void onDelete();
private:
	Boid* m_player;
	std::vector<Wall*> m_vectorpWalls;
	std::vector<Obstacle*> m_vectorpObstacles;
	std::vector<Laser*> m_vectorpLasers;
	std::vector<Wall*> m_vectorpPoweCells;
	std::vector<Boid*> m_vectorpBoids;
	BoidDescriptor playerDesc;
	BoidDescriptor TankDesc;
	BoidDescriptor TorretDesc;
};
