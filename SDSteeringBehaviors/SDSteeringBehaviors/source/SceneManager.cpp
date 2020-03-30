#include <SceneManager.h>
#include <sstream>  
SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::init(float* _deltaTime, StateMachine* _stateMachine)
{
	m_pDeltaTime = _deltaTime;
	m_stateMachine = _stateMachine;
	playerDesc.globalTime = _deltaTime;
	playerDesc.Direction = { 0 ,0 };
	playerDesc.Speed = 8;
	playerDesc.ratio = 10;
	playerDesc.masa = 0.7;
	playerDesc.seek.impetu = 10;
	playerDesc.ptr_obstacles = &m_vectorpObstacles;
	playerDesc.obstacleEvadeDimentions.impetu = 15;
	playerDesc.shapeColor = sf::Color::Green;
	playerDesc.pStateMachine = _stateMachine;
	playerDesc.BoidType = TYPEBOID::PLAYER;
	playerDesc.pWalls = &m_vectorpWalls;
	m_player = new Boid;
	TankDesc.globalTime = _deltaTime;
	TankDesc.ratio = 10;
	TankDesc.Speed = 7.8;
	TankDesc.masa = 0.2f;
	TankDesc.Position = CD::CDVector2(500, 500);
	TankDesc.ptr_obstacles = &m_vectorpObstacles;
	TankDesc.obstacleEvadeDimentions.impetu = 10;
	TankDesc.BoidType = TYPEBOID::TANK;
	TankDesc.pStateMachine = _stateMachine;
	TankDesc.ratioToLooking = 35;//tank
	TankDesc.AngleToLookingInDegrees = 60;
	TankDesc.pPlayer = m_player;
	TankDesc.DirectionView = { 1,0 };
	TankDesc.persu.impetu = 10;
	TankDesc.persu.timeProyection = 1;
	TankDesc.shapeColor = { 0, 0, 255, 255 };
	TankDesc.pWalls = &m_vectorpWalls;

	TorretDesc.globalTime = _deltaTime;
	TorretDesc.ratio = 5;
	TorretDesc.masa = 0.2f;
	TorretDesc.Position = CD::CDVector2(500, 500);
	TorretDesc.shapeColor = { 0, 0, 255, 255 };
	TorretDesc.ptr_obstacles = &m_vectorpObstacles;
	TorretDesc.obstacleEvadeDimentions.impetu = 20;
	TorretDesc.BoidType = TYPEBOID::TORRET;
	TorretDesc.pStateMachine = _stateMachine;
	TorretDesc.ratioToLooking = 100;//torret
	TorretDesc.AngleToLookingInDegrees = 60;
	TorretDesc.pPlayer = m_player;
	TorretDesc.DirectionView = { 1,0 };
	TorretDesc.persu.impetu = 10;
	TorretDesc.persu.timeProyection = 4;
	TorretDesc.rotateSpeed = 0.02;

	loadNextLevel();
}

void SceneManager::Update()
{


	for (size_t i = 0; i < m_vectorpBoids.size(); i++)
	{
		m_vectorpBoids[i]->Update();
	}
	//m_player.Render(_wind);
	for (size_t i = 0; i < m_vectorpLasers.size(); i++)
	{
		m_vectorpLasers[i]->update(m_vectorpBoids,m_player);
	}
	if (m_player->m_isDead)
	{
		m_bResetLevel = true;
		resetVars();
		m_bResetLevel = false;
	}
	checkIfPlayerTakeCell();
	checkIfPlayerIsOnWinPoint();
	//checkIfPlayerIsOnWinPoint();
}

void SceneManager::render(sf::RenderWindow& _wind)
{
	for (size_t i = 0; i < m_WallsIndexInitToFinal.size(); i++)
	{
		_wind.draw(wallsGeometri[i]);
	}
	for (size_t i = 0; i < m_vectorpWalls.size(); i++)
	{
		m_vectorpWalls[i]->render(_wind);
	}
	m_winPoint.render(_wind);
	for (size_t i = 0; i < m_vectorpObstacles.size(); i++)
	{
		m_vectorpObstacles[i]->Render(_wind);
	}
	for (size_t i = 0; i < m_vectorpPoweCells.size(); i++)
	{
		m_vectorpPoweCells[i]->render(_wind);
	}
	for (size_t i = 0; i < m_vectorpBoids.size(); i++)
	{
		m_vectorpBoids[i]->Render(_wind);
	}
	//m_player.Render(_wind);
	for (size_t i = 0; i < m_vectorpLasers.size(); i++)
	{
		m_vectorpLasers[i]->render(_wind);
	}
	_wind.draw(m_score);
}

void SceneManager::onDelete()
{
	
	for (size_t i = 0; i < m_vectorpWalls.size(); i++)
	{
		if (m_vectorpWalls[i] != nullptr)
		{
			delete m_vectorpWalls[i];
			m_vectorpWalls[i] = nullptr;
		}
	}
	m_vectorpWalls.clear();
	for (size_t i = 0; i < m_vectorpObstacles.size(); i++)
	{

		if (m_vectorpObstacles[i] != nullptr)
		{
			m_vectorpObstacles[i]->Delete();
			delete m_vectorpObstacles[i];
			m_vectorpObstacles[i] = nullptr;
		}
	}
	m_vectorpObstacles.clear();
	for (size_t i = 0; i < m_vectorpLasers.size(); i++)
	{
		if (m_vectorpLasers[i] != nullptr)
		{
			delete m_vectorpLasers[i];
			m_vectorpLasers[i] = nullptr;
		}
	}
	m_vectorpLasers.clear();
	for (size_t i = 0; i < m_vectorpPoweCells.size(); i++)
	{
		if (m_vectorpPoweCells[i] != nullptr)
		{
			delete m_vectorpPoweCells[i];
			m_vectorpPoweCells[i] = nullptr;
		}
	}
	m_vectorpPoweCells.clear();
	for (size_t i = 0; i < m_vectorpBoids.size(); i++)
	{
		if (m_vectorpBoids[i] != nullptr)
		{
			delete m_vectorpBoids[i];
			m_vectorpBoids[i] = nullptr;
		}
	}
	for (size_t i = 0; i < m_WallsIndexInitToFinal.size(); i++)
	{
		wallsGeometri[i].setPointCount(0);
	}
	m_WallsIndexInitToFinal.clear();
	m_WallsPositions.clear();
	
	m_vectorpBoids.clear();
}

void SceneManager::loadNextLevel()
{

	m_winPoint.m_bIsActived = false;
	m_PowerPointsToke = 0;
	if (!m_bAlreadyInit)
	{
		ifstream numLevelsFile;
		numLevelsFile.open("levels/numberoflevels.txt");
		numLevelsFile >> m_lastLevel;
		m_bAlreadyInit = true;

		numLevelsFile.close();
	}

	if (!m_bResetLevel)
	{
		++m_currentLevel;
	}
	if (m_currentLevel> 4)
	{
		m_currentLevel=1;
	}
	stringstream ss;
	ss << m_currentLevel;
	string s;
	ss >> s;
	std::string numberOfNewLevel = "levels/";
	numberOfNewLevel += s;
	ifstream myfile;
	myfile.open(numberOfNewLevel);
	string info;
	LECTOR m_currentLector = LECTOR::NONELECTOR;
	char* token = nullptr;
	char* nextToken = nullptr;
	CDVector2 newPos;
	CDVector2 newPos2;
	float RatioLooking;
	while (myfile >> info)
	{
		if (info == "PLAYER")
		{
			m_currentLector = LECTOR::PLAYERLECTOR;
			myfile >> info;
		}
		if (info == "BOIDS")
		{
			m_currentLector = LECTOR::BOIDSLECTOR;
			myfile >> info;
		}
		if (info == "LASERS")
		{
			m_currentLector = LECTOR::LASERSLECTOR;
			myfile >> info;
		}
		if (info == "POWERCELLS")
		{
			m_currentLector = LECTOR::POWERCELLLECTOR;
			myfile >> info;
		}
		if (info == "WALLS")
		{
			m_currentLector = LECTOR::WALLSLECTOR;
			myfile >> info;
		}
		if (info == "WALLSINDEX")
		{
			m_currentLector = LECTOR::WALLSINDEXLECTOR;
			myfile >> info;
		}
		if (info == "WINPOINT")
		{
			m_currentLector = LECTOR::WINPOINTLECTOR;
			myfile >> info;
		}
		switch (m_currentLector)
		{
		case LECTOR::PLAYERLECTOR:
			if (info == "POS:")
			{
				myfile >> info;
				float f = std::stof(info);//this is much better way to do it
				myfile >> info;
				float f2 = std::stof(info);//this is much better way to do it
				CDVector2 playerPos = { f,f2 };
				playerDesc.Position = playerPos;
				m_player->Init(playerDesc);
				m_vectorpBoids.push_back(m_player);
			}
			break;
		case LECTOR::BOIDSLECTOR:
			if (info == "POS:")
			{
				myfile >> info;
				float f = std::stof(info);//this is much better way to do it
				myfile >> info;
				float f2 = std::stof(info);//this is much better way to do it
				newPos = { f,f2 };
				myfile >> info;
			}
			if (info == "RATIOLOOKING:")
			{
				myfile >> info;
				float f = std::stof(info);//this is much better way to do it
				RatioLooking = f;
				myfile >> info;
			}
			if (info == "TYPE:")
			{
				myfile >> info;
				if (info == "TANK")
				{
					TankDesc.ratioToLooking = RatioLooking;
					TankDesc.Position = newPos;
					Boid* newBoid = new Boid;
					newBoid->Init(TankDesc);
					m_vectorpBoids.push_back(newBoid);
					newBoid = nullptr;
				}
				else if (info == "TORRET")
				{

					TorretDesc.ratioToLooking = RatioLooking;
					TorretDesc.Position = newPos;
					Boid* newBoid = new Boid;
					newBoid->Init(TorretDesc);
					m_vectorpBoids.push_back(newBoid);
					newBoid = nullptr;
				}
			}
			break;
		case LECTOR::LASERSLECTOR:
			if (info == "POS1:")
			{
				myfile >> info;
				float f = std::stof(info);//this is much better way to do it
				myfile >> info;
				float f2 = std::stof(info);//this is much better way to do it
				newPos = { f,f2 };
				myfile >> info;
			}
			if (info == "POS2:")
			{
				myfile >> info;
				float f = std::stof(info);//this is much better way to do it
				myfile >> info;
				float f2 = std::stof(info);//this is much better way to do it
				newPos2 = { f,f2 };
				Laser* newLaser = new Laser;
				newLaser->init(newPos, newPos2, m_pDeltaTime);
				m_vectorpLasers.push_back(newLaser);
				newLaser = nullptr;
			}
			break;
		case LECTOR::WALLSLECTOR:
			if (info == "POS:")
			{
				myfile >> info;
				float f = std::stof(info);//this is much better way to do it
				myfile >> info;
				float f2 = std::stof(info);//this is much better way to do it
				m_WallsPositions.push_back({ f,f2 });
			}
			break;
		case LECTOR::WALLSINDEXLECTOR:
			if (info == "INDEX:")
			{
				myfile >> info;
				float f = std::stof(info);//this is much better way to do it
				myfile >> info;
				float f2 = std::stof(info);//this is much better way to do it
				m_WallsIndexInitToFinal.push_back({ f,f2 });
			}
			break;
		case LECTOR::POWERCELLLECTOR:
			if (info == "POS:")
			{
				myfile >> info;
				float f = std::stof(info);//this is much better way to do it
				myfile >> info;
				float f2 = std::stof(info);//this is much better way to do it
				CDVector2 cellPos = { f,f2 };
				PowerCells* newCell = new PowerCells;
				newCell->init(cellPos);
				m_vectorpPoweCells.push_back(newCell);
				newCell = nullptr;
			}
			break;
		case LECTOR::WINPOINTLECTOR:
			if (info == "POS:")
			{
				myfile >> info;
				float f = std::stof(info);//this is much better way to do it
				myfile >> info;
				float f2 = std::stof(info);//this is much better way to do it
				m_winPoint.setPosition(f, f2);
				m_winPoint.init();
			}
			break;
		default:
			break;
		}
	}
	m_PowerPointsOfLevel = m_vectorpPoweCells.size();
	bool firstOne = true;
	wallsGeometri = new sf::ConvexShape[m_WallsIndexInitToFinal.size()];

	for (size_t i = 0; i < m_WallsIndexInitToFinal.size(); i++)
	{
		wallsGeometri[i].setPointCount(m_WallsIndexInitToFinal[i].y- m_WallsIndexInitToFinal[i].x+1);
		if (firstOne)
		{
			firstOne = false;
			wallsGeometri[i].setFillColor ({ 30,30,30,255 });
		}
		else
		{
			wallsGeometri[i].setFillColor({ 60,60,60,255 });
		}
		wallsGeometri[i].setOutlineColor({ 100,100,100,255 });
		wallsGeometri[i].setOutlineThickness(5);
		int index = 0;
		for (size_t j = m_WallsIndexInitToFinal[i].x; j < m_WallsIndexInitToFinal[i].y+1; j++)
		{
			Wall* newWall = new Wall;
			if (j== m_WallsIndexInitToFinal[i].y)
			{
				newWall->init(m_WallsPositions[j], m_WallsPositions[m_WallsIndexInitToFinal[i].x]);
				wallsGeometri[i].setPoint(index, sf::Vector2f(m_WallsPositions[j].x, m_WallsPositions[j].y));
			}
			else
			{
				newWall->init(m_WallsPositions[j], m_WallsPositions[j+1]);
				wallsGeometri[i].setPoint(index, sf::Vector2f(m_WallsPositions[j].x, m_WallsPositions[j].y));
			}
			m_vectorpWalls.push_back(newWall);
			newWall = nullptr;
			++index;
		}
	}
	initScore();
}


void SceneManager::checkIfPlayerTakeCell()
{
	for (size_t i = 0; i < m_vectorpPoweCells.size(); i++)
	{
		if (!m_vectorpPoweCells[i]->m_actived)
		{
			continue;
		}
		CDVector2 distanceVector = m_player->getPosition() - m_vectorpPoweCells[i]->getPosition();
		float distance = distanceVector.length();
		if (distance - m_player->getRatio() <= m_vectorpPoweCells[i]->getRatio())
		{
			m_vectorpPoweCells[i]->m_actived = false;
			++m_PowerPointsToke;
			updateScore();
			if (m_PowerPointsToke== m_PowerPointsOfLevel)
			{
				m_winPoint.m_bIsActived = true;
			}
		}
	}
}

void SceneManager::checkIfPlayerIsOnWinPoint()
{
	if (m_winPoint.m_bIsActived)
	{
		CDVector2 distanceVector = m_player->getPosition() - m_winPoint.getPosition();
		float distance = distanceVector.length();
		if (distance - m_player->getRatio() <= m_winPoint.getRatio())
		{
			resetVars();
			//loadNextLevel();
		}
	}
}

void SceneManager::resetVars()
{
	onDelete();
	init(m_pDeltaTime, m_stateMachine);
}

void SceneManager::initScore()
{
	if (!m_font.loadFromFile("CollegiateFLF.ttf"))
	{
		// error...
	}
	//g_text.setColor(sf::Color::White);CollegiateFLF.ttf
	stringstream ss;
	ss << m_PowerPointsToke;
	string s;
	ss >> s;
	stringstream ss2;
	ss2 << m_PowerPointsOfLevel;
	string s2;
	ss2 >> s2;
	string score = s;
	score += "/";
	score += s2;
	m_score.setString(score);
	m_score.setFont(m_font);
	m_score.setPosition(60, 0);
	m_score.setCharacterSize(18);
	m_score.setFillColor(sf::Color::Cyan);

}

void SceneManager::updateScore()
{
	stringstream ss;
	ss << m_PowerPointsToke;
	string s;
	ss >> s;
	stringstream ss2;
	ss2 << m_PowerPointsOfLevel;
	string s2;
	ss2 >> s2;
	string score = s;
	score += "/";
	score += s2;
	m_score.setString(score);
	m_score.setFont(m_font);
	m_score.setPosition(60, 0);
	m_score.setCharacterSize(18);
	m_score.setFillColor(sf::Color::Cyan);
}
