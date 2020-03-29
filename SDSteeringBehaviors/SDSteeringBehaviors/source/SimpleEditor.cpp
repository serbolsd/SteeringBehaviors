#include <SimpleEditor.h>
#include <sstream>  

SimpleEditor::SimpleEditor()
{
}

SimpleEditor::~SimpleEditor()
{
}

void SimpleEditor::Init(const float& windlength, const float& windWidth,float *_deltaTime,sf::RenderWindow*_wind)
{
	m_pDeltaTime = _deltaTime;
	m_pWind = _wind;
	m_windlength = windlength;
	m_windWidth = windWidth;
	initText();
	m_lastPoint.setRadius(4);
	m_lastPoint.setOrigin(4, 4);
	m_lastPoint.setFillColor(sf::Color::Yellow);

	m_winPoint.init();
	m_winPoint.setPosition(windlength / 2, windlength /4 );

	playerDesc.globalTime = _deltaTime;
	playerDesc.Direction = { 0 ,0 };
	playerDesc.Position = { windlength/2,windlength/2 };
	playerDesc.Speed = 8;
	playerDesc.ratio = 10;
	playerDesc.masa = 0.7;
	playerDesc.seek.impetu = 10;
	playerDesc.ptr_obstacles = &m_vectorpObstacles;
	playerDesc.obstacleEvadeDimentions.impetu = 15;
	playerDesc.shapeColor = sf::Color::Green;
	//playerDesc.pStateMachine = &g_stateMachine;
	playerDesc.BoidType = TYPEBOID::PLAYER;
	playerDesc.pWalls = &m_vectorpWalls;
	m_player = new Boid();
	m_player->Init(playerDesc);
	m_vectorpBoids.push_back(m_player);

	TankDesc.globalTime = _deltaTime;
	TankDesc.ratio = 10;
	TankDesc.Speed = 8;
	TankDesc.masa = 0.2f;
	TankDesc.Position = CD::CDVector2(500, 500);
	TankDesc.ptr_obstacles = &m_vectorpObstacles;
	TankDesc.obstacleEvadeDimentions.impetu = 10;
	TankDesc.BoidType = TYPEBOID::TANK;
	//TankDesc.pStateMachine = &g_stateMachine;
	TankDesc.ratioToLooking = 35;//tank
	TankDesc.AngleToLookingInDegrees = 60;
	TankDesc.pPlayer = m_player;
	TankDesc.DirectionView = { 1,0 };
	TankDesc.persu.impetu = 10;
	TankDesc.persu.timeProyection = 4;
	TankDesc.shapeColor = { 0, 0, 255, 255 };

	TorretDesc.globalTime = _deltaTime;
	TorretDesc.ratio = 5;
	TorretDesc.Speed = 2;
	TorretDesc.masa = 0.2f;
	TorretDesc.Position = CD::CDVector2(500, 500);
	TorretDesc.shapeColor = { 0, 0, 255, 255 };
	TorretDesc.ptr_obstacles = &m_vectorpObstacles;
	TorretDesc.obstacleEvadeDimentions.impetu = 20;
	TorretDesc.BoidType = TYPEBOID::TORRET;
	//TorretDesc.pStateMachine = &g_stateMachine;
	TorretDesc.ratioToLooking = 100;//torret
	TorretDesc.AngleToLookingInDegrees = 60;
	TorretDesc.pPlayer = m_player;
	TorretDesc.DirectionView = { 1,0 };
	TorretDesc.persu.impetu = 10;
	TorretDesc.persu.timeProyection = 4;
	TorretDesc.rotateSpeed = 0.02;
}

void SimpleEditor::Update()
{
	m_elapseTime += *m_pDeltaTime;
	inputs();
	switch (m_edit)
	{
	case CURRENTEDIT::NONE:
		break;
	case CURRENTEDIT::PLAYER:
		updateForPlayer();
		break;
	case CURRENTEDIT::TANKS:
		updateForEnemy();
		break;
	case CURRENTEDIT::TORRETS:
		updateForEnemy();
		break;
	case CURRENTEDIT::LASERS:
		updateForLser();
		break;
	case CURRENTEDIT::WALLS:
		updateForWalls();
		break;
	case CURRENTEDIT::POWERCELL:
		updateForPowerCell();
		break;
	case CURRENTEDIT::WINPOINT:
		updateForWinPoint();
		break;
	default:
		break;
	}
}

void SimpleEditor::render(sf::RenderWindow& _wind)
{
	if (isCliclekd)
	{
		_wind.draw(m_lastPoint);
	}
	
	for (size_t i = 0; i < m_vectorpWalls.size(); i++)
	{
		m_vectorpWalls[i]->render(_wind);
	}
	if (m_currentWall!=nullptr)
	{
		m_currentWall->render(_wind);
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
	if (currentBoid!=nullptr)
	{
		currentBoid->Render(_wind);
	}
	//m_player.Render(_wind);
	for (size_t i = 0; i < m_vectorpLasers.size(); i++)
	{
		m_vectorpLasers[i]->render(_wind);
	}
	if (m_currentLaser!=nullptr)
	{
		m_currentLaser->render(_wind);
	}
	for (size_t i = 0; i < 13; i++)
	{
		_wind.draw(m_text[i]);
	}
}

void SimpleEditor::onDelete()
{
	//m_player.Delete();
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
	m_vectorpBoids.clear();
	if (currentBoid!=nullptr)
	{
		delete currentBoid;
		currentBoid=nullptr;
	}
	if (m_currentLaser!=nullptr)
	{
		delete m_currentLaser;
		m_currentLaser=nullptr;
	}
}

void SimpleEditor::inputs()
{
	if (m_bMousePressed)
	{
		m_bMousePressed = false;
		delay = m_elapseTime + constDelayMouse;
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		sf::Vector2i Mpos = sf::Mouse::getPosition(*m_pWind);
		sf::Vector2f cordPos = m_pWind->mapPixelToCoords(Mpos);
		if (cordPos.x<0 && cordPos.x>m_windlength&& cordPos.y<0 && cordPos.y>m_windWidth)
		{

		}
		else if (m_elapseTime> delay || m_bMousePressed)
		{
			delay = m_elapseTime + constDelayMouse;
			m_bMousePressed = true;
			if (m_edit == CURRENTEDIT::PLAYER|| m_edit == CURRENTEDIT::WINPOINT)
			{
				m_edit = CURRENTEDIT::NONE;
				if (m_pcurrentText != nullptr)
				{
					m_pcurrentText->setFillColor(sf::Color::White);
					m_pcurrentText = nullptr;
				}
			}
			if (m_edit == CURRENTEDIT::TANKS || m_edit == CURRENTEDIT::TORRETS)
			{
				m_vectorpBoids.push_back(currentBoid);
				currentBoid = nullptr;
			}
			if (m_edit==CURRENTEDIT::POWERCELL)
			{
				m_vectorpPoweCells.push_back(m_currentPowerCell);
				m_currentPowerCell = nullptr;
			}
			if (m_edit == CURRENTEDIT::LASERS || m_edit == CURRENTEDIT::WALLS)
			{
				m_pointsForLaserAndWalls.push_back({ cordPos.x,cordPos.y});
				if (m_edit == CURRENTEDIT::WALLS&& m_currentWall!=nullptr)
				{
					m_vectorpWalls.push_back(m_currentWall);
					m_currentWall = nullptr;
				}
			}
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1))
	{
		resetCurrentBoid();
		m_edit= CURRENTEDIT::PLAYER;
		rePaintCurrentText(m_text[0]);
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2))
	{
		resetCurrentBoid();
		m_edit = CURRENTEDIT::TANKS;
		rePaintCurrentText(m_text[1]);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num3))
	{
		resetCurrentBoid();
		m_edit = CURRENTEDIT::TORRETS;
		rePaintCurrentText(m_text[2]);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num4))
	{
		resetCurrentBoid();
		m_edit = CURRENTEDIT::LASERS;
		rePaintCurrentText(m_text[3]);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num5))
	{
		resetCurrentBoid();
		m_edit = CURRENTEDIT::WALLS;
		rePaintCurrentText(m_text[4]);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num6))
	{
		resetCurrentBoid();
		m_edit = CURRENTEDIT::POWERCELL;
		rePaintCurrentText(m_text[5]);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num7))
	{
		resetCurrentBoid();
		m_edit = CURRENTEDIT::WINPOINT;
		rePaintCurrentText(m_text[6]);
	}	
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num9))
	{
		if (currentBoid!=nullptr)
		{
			currentBoid->setRatioToLooking(currentBoid->m_myDesc.ratioToLooking + 1);
		}
		//addRatio
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num8))
	{
		if (currentBoid != nullptr)
		{
			currentBoid->setRatioToLooking(currentBoid->m_myDesc.ratioToLooking - 1);
		}
		//subtractRatio
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
	{
		resetCurrentBoid();
		m_edit = CURRENTEDIT::NONE;
		if (m_pcurrentText != nullptr)
		{
			m_pcurrentText->setFillColor(sf::Color::White);
			m_pcurrentText = nullptr;
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::BackSlash))
	{
		resetCurrentBoid();
		//deshacer
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
	{
		resetCurrentBoid();
		if (m_elapseTime >delay || m_bMousePressed)
		{
			delay = m_elapseTime + constDelayMouse;
			m_bMousePressed = true;
			saveLevel();
		}
		//deshacer
	}
}

void SimpleEditor::rePaintCurrentText(sf::Text& _text)
{
	if (m_pcurrentText != nullptr)
	{
		m_pcurrentText->setFillColor(sf::Color::White);
	}
	m_pcurrentText = &_text;
	m_pcurrentText->setFillColor(sf::Color::Green);
}

void SimpleEditor::resetCurrentBoid()
{
	if (currentBoid != nullptr)
	{
		delete currentBoid;
		currentBoid = nullptr;
	}
	if (m_currentLaser != nullptr)
	{
		delete m_currentLaser;
		m_currentLaser = nullptr;
	}
	if (m_currentPowerCell != nullptr)
	{
		delete m_currentPowerCell;
		m_currentPowerCell = nullptr;
	}
	if (m_edit==CURRENTEDIT::WALLS&& m_pointsForLaserAndWalls.size()>0)
	{
		m_currentWall = new Wall();
		m_currentWall->init(m_pointsForLaserAndWalls[m_pointsForLaserAndWalls.size() - 1], m_pointsForLaserAndWalls[0]);
		m_vectorpWalls.push_back(m_currentWall);
		m_WallsIndexing.y = m_vectorpWalls.size()-1;
		m_WallsIndexInitToFinal.push_back(m_WallsIndexing);
		m_currentWall = nullptr;
		m_bIsIndexResgister = false;
	}
	m_pointsForLaserAndWalls.clear();
}

void SimpleEditor::updateForPlayer()
{
	sf::Vector2i Mpos = sf::Mouse::getPosition(*m_pWind);
	sf::Vector2f cordPos = m_pWind->mapPixelToCoords(Mpos);
	m_player->setPosicion({cordPos.x,cordPos.y});
}

void SimpleEditor::updateForWinPoint()
{
	sf::Vector2i Mpos = sf::Mouse::getPosition(*m_pWind);
	sf::Vector2f cordPos = m_pWind->mapPixelToCoords(Mpos);
	m_winPoint.setPosition( cordPos.x,cordPos.y );
}

void SimpleEditor::updateForEnemy()
{
	if (currentBoid==nullptr)
	{
		currentBoid = new Boid;
		if (m_edit==CURRENTEDIT::TANKS)
		{
			currentBoid->Init(TankDesc);
		}
		if (m_edit == CURRENTEDIT::TORRETS)
		{
			currentBoid->Init(TorretDesc);
		}
	}
	sf::Vector2i Mpos = sf::Mouse::getPosition(*m_pWind);
	sf::Vector2f cordPos = m_pWind->mapPixelToCoords(Mpos);
	currentBoid->setPosicion({ cordPos.x,cordPos.y });
}

void SimpleEditor::updateForLser()
{
	sf::Vector2i Mpos = sf::Mouse::getPosition(*m_pWind);
	sf::Vector2f cordPos = m_pWind->mapPixelToCoords(Mpos);

	if (m_currentLaser==nullptr&& m_pointsForLaserAndWalls.size()==1)
	{
		m_currentLaser = new Laser();
		m_currentLaser->init(m_pointsForLaserAndWalls[0], { cordPos.x,cordPos.y},m_pDeltaTime);
	}
	if (m_currentLaser != nullptr && m_pointsForLaserAndWalls.size()==2)
	{
		Laser* newLaser = new Laser();
		newLaser->init(m_pointsForLaserAndWalls[0], m_pointsForLaserAndWalls[1], m_pDeltaTime);
		m_vectorpLasers.push_back(newLaser);
		m_pointsForLaserAndWalls.clear();
		delete m_currentLaser;
		m_currentLaser = nullptr;
		m_edit = CURRENTEDIT::NONE;
		if (m_pcurrentText != nullptr)
		{
			m_pcurrentText->setFillColor(sf::Color::White);
			m_pcurrentText = nullptr;
		}
		resetCurrentBoid();
	}
	if (m_currentLaser != nullptr)
	{
		m_currentLaser->init(m_pointsForLaserAndWalls[0], { cordPos.x,cordPos.y }, m_pDeltaTime);

	}
}

void SimpleEditor::updateForPowerCell()
{
	sf::Vector2i Mpos = sf::Mouse::getPosition(*m_pWind);
	sf::Vector2f cordPos = m_pWind->mapPixelToCoords(Mpos);
	if (m_currentPowerCell==nullptr)
	{
		m_currentPowerCell = new PowerCells;
		m_currentPowerCell->init({ cordPos.x,cordPos.y });
	}
	m_currentPowerCell->setPosition({ cordPos.x,cordPos.y});
}

void SimpleEditor::updateForWalls()
{
	sf::Vector2i Mpos = sf::Mouse::getPosition(*m_pWind);
	sf::Vector2f cordPos = m_pWind->mapPixelToCoords(Mpos);

	if (m_currentWall == nullptr && m_pointsForLaserAndWalls.size() >0)
	{
		if (!m_bIsIndexResgister)
		{
			m_bIsIndexResgister = true;
			m_WallsIndexing.x = m_vectorpWalls.size();
		}
		m_currentWall = new Wall();
		m_currentWall->init(m_pointsForLaserAndWalls[m_pointsForLaserAndWalls.size()-1], { cordPos.x,cordPos.y });
	}
	else if(m_currentWall != nullptr)
	{
		m_currentWall->init(m_pointsForLaserAndWalls[m_pointsForLaserAndWalls.size() - 1], { cordPos.x,cordPos.y });
	}
}

void SimpleEditor::initText()
{
	if (!m_font.loadFromFile("CollegiateFLF.ttf"))
	{
		// error...
	}
	//g_text.setColor(sf::Color::White);CollegiateFLF.ttf
	m_text[0].setString("1-SET PLAYER POSITION");
	m_text[1].setString("2-SET TANK");
	m_text[2].setString("3-SET TOORET");
	m_text[3].setString("4-CREATE LASER (TWO CLICKS)");
	m_text[4].setString("5-CREATE WALLS (ANY CLICKS, the first is the limited map)");
	m_text[5].setString("6-SET POWERCELL");
	m_text[6].setString("7-SET WINPONT");
	m_text[7].setString("8-SUBTRACT RATIO DETECCTION OF CURRENT ENEMY");
	m_text[8].setString("9-ADD RATIO DETECCTION OF CURRENT ENEMY");
	m_text[9].setString("BACK-REMOVE LAST ACTION");
	m_text[10].setString("ENTER-COMPLETE ACTION");
	m_text[11].setString("CLICK TO PUT POSITION");
	m_text[12].setString("S- SAVE LEVEL");
	int nexPosPixel = 15;
	for (int i = 0; i < 13; i++)
	{
		m_text[i].setFont(m_font);
		m_text[i].setPosition(0, nexPosPixel);
		m_text[i].setCharacterSize(14);
		m_text[i].setFillColor(sf::Color::White);
		//m_text[i].setStyle(sf::Text::Bold | sf::Text::Underlined);
		nexPosPixel += 15;
	}
}

void SimpleEditor::saveLevel()
{
	//numberoflevels.txt
	ifstream myfile;
	myfile.open("levels/numberoflevels.txt");
	int numberOfLevels = 0;
	myfile >> numberOfLevels;
	++numberOfLevels;
	stringstream ss;
	ss << numberOfLevels;
	string s;
	ss >> s;
	std::string numberOfNewLevel="levels/";
	numberOfNewLevel+=s;

	std::ofstream outfile1("levels/numberoflevels.txt");

	outfile1 << numberOfLevels << std::endl;
	outfile1.close();

	std::ofstream outfile(numberOfNewLevel);

	outfile << "PLAYER" << std::endl;
	outfile << "POS: "<<m_player->getPosition().x<<" "<< m_player->getPosition().y << std::endl;
	outfile << "BOIDS" << std::endl;
	for (int i = 0; i < m_vectorpBoids.size(); i++)
	{
		if (m_vectorpBoids[i]==m_player)
		{
			continue;
		}
		outfile << "POS: "<< m_vectorpBoids[i]->getPosition().x<<" "<< m_vectorpBoids[i]->getPosition().y << std::endl;
		outfile << "RATIOLOOKING: "<< m_vectorpBoids[i]->m_myDesc.ratioToLooking<< std::endl;
		if (m_vectorpBoids[i]->m_myDesc.BoidType==TYPEBOID::TANK)
		{
			outfile << "TYPE: " << "TANK" << std::endl;
		}
		else
		{
			outfile << "TYPE: " << "TORRET" << std::endl;
		}
	}
	outfile << "LASERS" << std::endl;
	for (size_t i = 0; i < m_vectorpLasers.size(); i++)
	{
		outfile << "POS1: " << m_vectorpLasers[i]->getPos1().x<< " " << m_vectorpLasers[i]->getPos1().y << std::endl;
		outfile << "POS2: " << m_vectorpLasers[i]->getPos2().x << " " << m_vectorpLasers[i]->getPos2().y << std::endl;
	}
	outfile << "POWERCELLS" << std::endl;
	for (size_t i = 0; i < m_vectorpPoweCells.size(); i++)
	{
		outfile << "POS: " << m_vectorpPoweCells[i]->getPosition().x << " " << m_vectorpPoweCells[i]->getPosition().y << std::endl;
	}
	outfile << "WALLS" << std::endl;
	for (size_t i = 0; i < m_vectorpWalls.size(); i++)
	{
		outfile << "POS: " << m_vectorpWalls[i]->getPos1().x << " " << m_vectorpWalls[i]->getPos1().y << std::endl;
	}
	outfile << "WALLSINDEX" << std::endl;
	for (size_t i = 0; i < m_WallsIndexInitToFinal.size(); i++)
	{
		outfile << "INDEX: " << m_WallsIndexInitToFinal[i].x << " " << m_WallsIndexInitToFinal[i].y << std::endl;
	}
	outfile << "WINPOINT" << std::endl;
	outfile << "POS: " << m_winPoint.getPosition().x << " " << m_winPoint.getPosition().y << std::endl;
	outfile.close();
}
