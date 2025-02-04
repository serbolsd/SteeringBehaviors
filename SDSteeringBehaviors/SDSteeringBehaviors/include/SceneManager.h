#pragma once
#include <CDVectors.h>
#include <SFML/Graphics.hpp>
#include <Boid.h>
#include <Obstacle.h>
#include <Wall.h>
#include <PowerCells.h>
#include <Laser.h>
#include <vector>
#include <winPoint.h>
#include <fstream>
using namespace std;
enum class LECTOR
{
	NONELECTOR = 0,
	PLAYERLECTOR,
	BOIDSLECTOR,
	LASERSLECTOR,
	WALLSLECTOR,
	WALLSINDEXLECTOR,
	POWERCELLLECTOR,
	WINPOINTLECTOR
};
class SceneManager
{
public:
	SceneManager();
	~SceneManager();
	void init(float* _deltaTime,StateMachine* _stateMachine);
	void Update();
	void render(sf::RenderWindow& _wind);
	void onDelete();
private:
	void loadNextLevel();
	void checkIfPlayerTakeCell();
	void checkIfPlayerIsOnWinPoint();
	void resetVars();
	void initScore();
	void updateScore();
	Boid* m_player;
	WinPoint m_winPoint;
	std::vector<Wall*> m_vectorpWalls;
	std::vector<CDVector2> m_WallsIndexInitToFinal;
	std::vector<CDVector2> m_WallsPositions;
	std::vector<Obstacle*> m_vectorpObstacles;
	std::vector<Laser*> m_vectorpLasers;
	std::vector<PowerCells*> m_vectorpPoweCells;
	std::vector<Boid*> m_vectorpBoids;
	BoidDescriptor playerDesc;
	BoidDescriptor TankDesc;
	BoidDescriptor TorretDesc;
	int m_currentLevel = 0;
	int m_lastLevel = 0;
	int m_PowerPointsOfLevel = 0;
	int m_PowerPointsToke = 0;
	sf::ConvexShape* wallsGeometri;
	float* m_pDeltaTime = nullptr;
	StateMachine* m_stateMachine;
	bool m_bResetLevel = false;
	sf::Font m_font;
	sf::Text m_score;
	bool m_bAlreadyInit = false;
};
