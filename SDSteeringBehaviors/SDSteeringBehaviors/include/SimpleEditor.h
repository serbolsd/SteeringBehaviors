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
enum class CURRENTEDIT
{
	NONE = 0,
	PLAYER,
	TANKS,
	TORRETS,
	LASERS,
	WALLS,
	POWERCELL,
	WINPOINT
};
class SimpleEditor
{
public:
	SimpleEditor();
	~SimpleEditor();
	void Init(const float& windlength, const float& windWidth, float* _deltaTime, sf::RenderWindow* _wind);
	void Update();
	void render(sf::RenderWindow& _wind);
	void onDelete();
	void inputs();
private:
	void rePaintCurrentText(sf::Text &_text);
	void resetCurrentBoid();
	void updateForPlayer();
	void updateForWinPoint();
	void updateForEnemy();
	void updateForLser();
	void updateForPowerCell();
	void updateForWalls();
	void initText();
	void saveLevel();
	float m_windlength;
	float m_windWidth;
	Boid* m_player;
	WinPoint m_winPoint;
	std::vector<Wall*> m_vectorpWalls;
	std::vector<CDVector2> m_WallsIndexInitToFinal;
	std::vector<Obstacle*> m_vectorpObstacles;
	std::vector<Laser*> m_vectorpLasers;
	std::vector<PowerCells*> m_vectorpPoweCells;
	std::vector<Boid*> m_vectorpBoids;
	std::vector<CDVector2> m_pointsForLaserAndWalls;
	CDVector2 m_WallsIndexing;
	//std::vector<std::vector<CDVector2*>> g_PathsVectors;
	BoidDescriptor playerDesc;
	BoidDescriptor TankDesc;
	BoidDescriptor TorretDesc;
	sf::CircleShape m_lastPoint;
	Boid* currentBoid=nullptr;
	Laser* m_currentLaser=nullptr;
	PowerCells* m_currentPowerCell=nullptr;
	Wall* m_currentWall=nullptr;
	bool isCliclekd = false;
	CDVector2 m_posLastPoit = { -1,-1 };
	sf::Text m_text[13];
	sf::Text* m_pcurrentText=nullptr;
	sf::Font m_font;
	CURRENTEDIT m_edit = CURRENTEDIT::NONE;
	sf::RenderWindow* m_pWind;
	float* m_pDeltaTime=nullptr;
	float m_elapseTime;
	float delay = 0;
	const float constDelayMouse = 0.5;
	bool m_bMousePressed = false;
	bool m_bIsIndexResgister = false;
};
