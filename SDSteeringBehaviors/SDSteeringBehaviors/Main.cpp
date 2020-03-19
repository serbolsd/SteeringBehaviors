#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Boid.h"
#include "Obstacle.h"
void Init();
void ObstaclesInit();
void BoidsInit();
void Update();
void Render();
void Input();
void Delete();
sf::RenderWindow g_wind(sf::VideoMode(900, 900), "window");

CD::CDVector2 g_MousePosition;
std::vector<Boid*> g_boidsVector;
std::vector<Obstacle*> g_ObstaclesVector;
std::vector<CD::CDVector2> g_pointsPathVector;
float g_deltaTime;

int main()
{
	//sum(); 
	
	Init();
	g_wind.setFramerateLimit(40);
	sf::RenderWindow createWin;
	sf::Event event;
	sf::Clock clock;
	sf::Time currentTime;
	sf::Time deltaTime;
	
	while (g_wind.isOpen())
	{
		clock.restart();
		//system("cls");
		while (g_wind.pollEvent(event))
		{
			if (event.type == sf::Event::Closed||
				event.key.code == sf::Keyboard::Escape)
				g_wind.close();
			

		}
		g_wind.clear(sf::Color(0, 0, 0, 0));
		Update();
		Render();
		g_wind.display();
		deltaTime = clock.getElapsedTime();
		g_deltaTime = deltaTime.asSeconds();
	}
	Delete();
	return 0;
}

void Init()
{
	g_deltaTime = 0;
	//g_MousePosition = new CD::CDVector2;
	//g_Path = new std::vector<CD::CDVector2>;
	g_pointsPathVector.push_back(CD::CDVector2(400,400));
	g_pointsPathVector.push_back(CD::CDVector2(800, 400));
	g_pointsPathVector.push_back(CD::CDVector2(600, 800));
	ObstaclesInit();
	BoidsInit();
}

void ObstaclesInit()
{
	Obstacle *firstObstacle = new Obstacle();
	Obstacle *SecondObstacle = new Obstacle();
	std::vector<Obstacle*>::iterator iteratorObstaclesVector;
	iteratorObstaclesVector = g_ObstaclesVector.begin();
	//obstacles = new std::vector<Obstacle*>;
	ObstacleDescriptor obstacleDesc;
	obstacleDesc.ratio = 40;
	obstacleDesc.position = { 200,200 };
	firstObstacle->Init(obstacleDesc);
	iteratorObstaclesVector=g_ObstaclesVector.insert(iteratorObstaclesVector ,firstObstacle);
	obstacleDesc.ratio = 20;
	obstacleDesc.position = { 280,240 };
	SecondObstacle->Init(obstacleDesc);
	iteratorObstaclesVector = g_ObstaclesVector.insert(iteratorObstaclesVector, SecondObstacle);
}

void BoidsInit()
{
	Boid* boid = new Boid();
	Boid* wanderRan = new Boid();
	Boid* wanderTime = new Boid();
	Boid* wader = new Boid();
	Boid* pathFollower = new Boid();
	Boid* patroler = new Boid();
	std::vector<Boid*>::iterator iteratorBoidsVector;
	iteratorBoidsVector = g_boidsVector.begin();
	BoidDescriptor descSeek;
	descSeek.globalTime = &g_deltaTime;
	descSeek.Direction = { 0 ,0 };
	descSeek.Position = { 500,500 };
	descSeek.Speed = 3;
	descSeek.ratio = 20;
	descSeek.masa = 0.1f;
	descSeek.seek.impetu = 10;
	descSeek.seek.objetive = &g_MousePosition;
	descSeek.ptr_obstacles = &g_ObstaclesVector;
	descSeek.obstacleEvadeDimentions.impetu=15;
	boid->Init(descSeek);
	iteratorBoidsVector = g_boidsVector.insert(iteratorBoidsVector,boid);
	/*BoidDescriptor descForEvade;
	descForEvade.m_Direction = { 0,0 };
	descForEvade.Position = { 600,600 };
	descForEvade.m_Speed = 1;
	descForEvade.shapeColor = { 255,0,0,255 };
	descForEvade.evade.impetu = 10;
	descForEvade.evade.objetive = &boid;
	descForEvade.evade.timeProyection = 5;
	BoidDescriptor descForPersu;
	descForPersu.m_Direction = { 0,0 };
	descForPersu.Position = { 600,600 };
	descForPersu.m_Speed = 1;
	descForPersu.shapeColor = { 255,0,0,255 };
	descForPersu.persu.impetu = 10;
	descForPersu.persu.objetive = &boid;
	descForPersu.persu.timeProyection = 15;
	PersuOrEvadeboid.Init(descForPersu);
	return;*/
	BoidDescriptor wanderRandDesc;
	wanderRandDesc.wander.type = TypeWander::WanderTypeRandom;
	wanderRandDesc.wander.limitsX = CD::CDVector2(0, 900);
	wanderRandDesc.wander.limitsY = CD::CDVector2(0, 900);
	wanderRandDesc.wander.impetu = 10;
	wanderRandDesc.globalTime = &g_deltaTime;
	wanderRandDesc.ratio = 4;
	wanderRandDesc.Speed = 1;
	wanderRandDesc.Position = CD::CDVector2(400, 400);
	wanderRandDesc.shapeColor = { 255, 0, 0, 255 };
	BoidDescriptor wanderTimeDesc;
	wanderTimeDesc.wander.type = TypeWander::wanderTypeTime;
	wanderTimeDesc.wander.limitsX = CD::CDVector2(0, 900);
	wanderTimeDesc.wander.limitsY = CD::CDVector2(0, 900);
	wanderTimeDesc.wander.impetu = 10;
	wanderTimeDesc.wander.timeToNextPoint = 3;
	wanderTimeDesc.globalTime = &g_deltaTime;
	wanderTimeDesc.ratio = 4;
	wanderTimeDesc.Speed = 1;
	wanderTimeDesc.Position = CD::CDVector2(200, 200);
	wanderTimeDesc.shapeColor = { 0, 255, 0, 255 };
	BoidDescriptor wanderDesc;
	wanderDesc.wander.type = TypeWander::WanderTypeVision;
	wanderDesc.wander.ratio = 5;
	wanderDesc.wander.openingAngleInDegrees = 20;
	wanderDesc.wander.impetu = 10;
	wanderDesc.wander.DistoToPointProyection = 10;
	wanderDesc.globalTime = &g_deltaTime;
	wanderDesc.ratio = 4;
	wanderDesc.Speed = 1;
	wanderDesc.Position = CD::CDVector2(500, 500);
	wanderDesc.shapeColor = { 0, 0, 255, 255 };

	//wanderRan.Init(wanderRandDesc);
	//boids->push_back(&wanderRan);
	//wanderTime.Init(wanderTimeDesc);
	//boids->push_back(&wanderTime);
	//wader.Init(wanderDesc);
	//boids->push_back(&wader);

	BoidDescriptor folloPathDes;
	folloPathDes.followPath.IndexPoint = 0;
	folloPathDes.followPath.impetu = 10;
	folloPathDes.followPath.Points = &g_pointsPathVector;
	folloPathDes.followPath.ratio = 30;
	folloPathDes.globalTime = &g_deltaTime;
	folloPathDes.ratio = 4;
	folloPathDes.Speed = 4;
	folloPathDes.masa = 0.2f;
	folloPathDes.Position = CD::CDVector2(500, 500);
	folloPathDes.shapeColor = { 0, 0, 255, 255 };

	//pathFollower.Init(folloPathDes);
	//boids->push_back(&pathFollower);

	BoidDescriptor patrolDesc;
	patrolDesc.globalTime = &g_deltaTime;
	patrolDesc.ratio = 4;
	patrolDesc.Speed = 4;
	patrolDesc.masa = 0.2f;
	patrolDesc.Position = CD::CDVector2(500, 500);
	patrolDesc.shapeColor = { 0, 0, 255, 255 };
	patrolDesc.patrol.indexPath = 0;
	patrolDesc.patrol.Points = &g_pointsPathVector;
	patrolDesc.patrol.impetu = 10;
	patrolDesc.patrol.Ratio = 30;
	patrolDesc.patrol.type = TypePatrol::PatrolTypeInverted;
	patrolDesc.patrol.timeToStay = 2;

	//patroler.Init(patrolDesc);
	//boids->push_back(&patroler);
	//
	//patrolDesc.shapeColor = { 0, 255, 0, 255 };
	//patrolDesc.masa = 0.2f;
	//patrolDesc.Speed = 5;
	//patrolDesc.patrol.type = TypePatrol::PatrolTypeCircuit;
	//pathFollower.Init(patrolDesc);
	//boids->push_back(&pathFollower);

	BoidDescriptor flockingDesc;
	flockingDesc.globalTime = &g_deltaTime;
	flockingDesc.ratio = 8;
	flockingDesc.Speed = 1;
	flockingDesc.Position = CD::CDVector2(500, 500);
	flockingDesc.shapeColor = { 0, 0, 255, 255 };
	flockingDesc.flocking.Boids = &g_boidsVector;
	flockingDesc.flocking.impetuDirection = 20;
	flockingDesc.flocking.impetuCohesion = 5;
	flockingDesc.flocking.impetuSeparation = 50;
	flockingDesc.flocking.ratioVision = 30;

	//boid.Init(flockingDesc);
	//boids->push_back(&boid);
	//
	//flockingDesc.ratio = 15;
	//flockingDesc.Position = CD::CDVector2(510, 500);
	//flockingDesc.shapeColor = { 255, 0, 0, 255 };
	//wanderRan.Init(flockingDesc);
	//boids->push_back(&wanderRan);
	//
	//flockingDesc.ratio = 8;
	//flockingDesc.Position = CD::CDVector2(500, 510);
	//flockingDesc.shapeColor = { 0, 255, 0, 255 };
	//wanderTime.Init(flockingDesc);
	//boids->push_back(&wanderTime);
	//
	//flockingDesc.ratio = 12;
	//flockingDesc.Position = CD::CDVector2(510, 510);
	//flockingDesc.shapeColor = { 255, 0, 255, 255 };
	//wader.Init(flockingDesc);
	//boids->push_back(&wader);
	//
	//flockingDesc.ratio = 12;
	//flockingDesc.Position = CD::CDVector2(520, 500);
	//flockingDesc.shapeColor = { 0, 255, 255, 255 };
	//pathFollower.Init(flockingDesc);
	//boids->push_back(&pathFollower);
	//
	//flockingDesc.ratio = 10;
	//flockingDesc.Position = CD::CDVector2(500, 520);
	//flockingDesc.shapeColor = { 255, 255, 0, 255 };
	//patroler.Init(flockingDesc);
	//boids->push_back(&patroler);
	
	BoidDescriptor FollowTheLeaderDesc;
	FollowTheLeaderDesc.globalTime = &g_deltaTime;
	FollowTheLeaderDesc.ratio = 20;
	FollowTheLeaderDesc.Speed = 2;
	FollowTheLeaderDesc.masa = 0.2f;
	FollowTheLeaderDesc.Position = CD::CDVector2(500, 500);
	FollowTheLeaderDesc.shapeColor = { 0, 0, 255, 255 };
	FollowTheLeaderDesc.followLeader.Boids = &g_boidsVector;
	FollowTheLeaderDesc.followLeader.impetu = 10;
	FollowTheLeaderDesc.followLeader.impetuFollow = 10;
	FollowTheLeaderDesc.followLeader.impetuEvade = 20;
	FollowTheLeaderDesc.followLeader.impetuDirection = 2;
	FollowTheLeaderDesc.followLeader.impetuCohesion = 2;
	FollowTheLeaderDesc.followLeader.impetuSeparation = 10;
	FollowTheLeaderDesc.followLeader.ratioVision = 30;
	FollowTheLeaderDesc.followLeader.distToLeader = 50;
	FollowTheLeaderDesc.followLeader.Leader = boid;
	FollowTheLeaderDesc.ptr_obstacles = &g_ObstaclesVector;
	FollowTheLeaderDesc.obstacleEvadeDimentions.impetu =20 ;

	BoidDescriptor descArrive;
	descArrive.globalTime = &g_deltaTime;
	descArrive.Direction = { 0 ,0 };
	descArrive.Position = { 500,500 };
	descArrive.Speed = 2;
	descArrive.ratio = 15;
	descArrive.masa = 0.1f;
	descArrive.arrive.impetu = 10;
	descArrive.arrive.objetive = &g_MousePosition;
	descArrive.arrive.ratio = 20;
	descArrive.ptr_obstacles = &g_ObstaclesVector;
	descArrive.obstacleEvadeDimentions.impetu = 10;

	//boid.Init(descArrive);
	//boids->push_back(&boid);
	
	FollowTheLeaderDesc.Position = CD::CDVector2(520, 500);
	FollowTheLeaderDesc.shapeColor = { 255, 0, 0, 255 };
	wanderRan->Init(FollowTheLeaderDesc);
	iteratorBoidsVector = g_boidsVector.insert(iteratorBoidsVector, wanderRan);
	
	FollowTheLeaderDesc.Position = CD::CDVector2(500, 520);
	FollowTheLeaderDesc.shapeColor = { 0, 255, 0, 255 };
	wanderTime->Init(FollowTheLeaderDesc);
	iteratorBoidsVector = g_boidsVector.insert(iteratorBoidsVector, wanderTime);
	
	FollowTheLeaderDesc.Position = CD::CDVector2(520, 520);
	FollowTheLeaderDesc.shapeColor = { 255, 0, 255, 255 };
	wader->Init(FollowTheLeaderDesc);
	iteratorBoidsVector = g_boidsVector.insert(iteratorBoidsVector, wader);
	
	FollowTheLeaderDesc.Position = CD::CDVector2(540, 500);
	FollowTheLeaderDesc.shapeColor = { 0, 255, 255, 255 };
	pathFollower->Init(FollowTheLeaderDesc);
	iteratorBoidsVector = g_boidsVector.insert(iteratorBoidsVector, pathFollower);
	
	FollowTheLeaderDesc.Position = CD::CDVector2(500, 540);
	FollowTheLeaderDesc.shapeColor = { 255, 255, 0, 255 };
	patroler->Init(FollowTheLeaderDesc);
	iteratorBoidsVector = g_boidsVector.insert(iteratorBoidsVector, patroler);
}

void Update()
{
	sf::Vector2i Mpos=sf::Mouse::getPosition(g_wind);
	sf::Vector2f cordPos=g_wind.mapPixelToCoords(Mpos);
	g_MousePosition.x = cordPos.x;
	g_MousePosition.y = cordPos.y;
	//boid.Update();
	//PersuOrEvadeboid.Update();
	for(int i=0; i< g_boidsVector.size();i++)
	{
		g_boidsVector[i]->Update();
	}
}

void Render()
{
	//boid.Render(*wind);
	//PersuOrEvadeboid.Render(*wind);
	for (int i = 0; i < g_ObstaclesVector.size(); i++)
	{
		g_ObstaclesVector[i]->Render(g_wind);
	}
	for (int i = 0; i < g_boidsVector.size(); i++)
	{
		g_boidsVector[i]->Render(g_wind);
	}
}

void Input()
{
}

void Delete()
{
	//boid.Delete();
	//delete dtime;
	for (int i = 0; i < g_ObstaclesVector.size(); i++)
	{
		if (g_ObstaclesVector[i]!=nullptr)
		{
			delete g_ObstaclesVector[i];
		}
		//obstacles[0][i]->Delete();
		//delete boids[0][i];
	}
	for (int i = 0; i < g_boidsVector.size(); i++)
	{
		if (g_boidsVector[i] != nullptr)
		{
			delete g_boidsVector[i];
		}
		//boids[0][i]->Delete();
		//delete boids[0][i];
	}
}