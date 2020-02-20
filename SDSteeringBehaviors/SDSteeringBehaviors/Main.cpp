#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Boid.h"
void Init();
void Update();
void Render();
void Input();
void Delete();
sf::RenderWindow* wind;
Boid boid;
Boid wanderRan;
Boid wanderTime;
Boid wader;
Boid pathFollower;
Boid patroler;
CD::CDVector2 *MousePosition;
std::vector<Boid*> *boids;
std::vector<CD::CDVector2> *path;
float *dtime;
int main()
{
	//sum();
	wind= new sf::RenderWindow(sf::VideoMode(900, 900), "window");
	Init();
	wind->setFramerateLimit(60);
	sf::Event event;
	sf::Clock clock;
	sf::Time currentTime;
	sf::Time deltaTime;
	
	while (wind->isOpen())
	{
		clock.restart();
		//system("cls");
		while (wind->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				wind->close();
			if (event.key.code == sf::Keyboard::Escape)
			{
				wind->close();
			}

		}
		wind->clear(sf::Color(0, 0, 0, 0));
		Update();
		Render();
		wind->display();
		deltaTime = clock.getElapsedTime();
		*dtime = deltaTime.asSeconds();
	}
	Delete();
	return 0;
}

void Init()
{
	dtime = new float(0);
	MousePosition = new CD::CDVector2;
	path = new std::vector<CD::CDVector2>;
	path->push_back(CD::CDVector2(400,400));
	path->push_back(CD::CDVector2(800, 400));
	path->push_back(CD::CDVector2(600, 800));
	boids = new std::vector<Boid*>;
	BoidDescriptor desc;
	desc.globalTime = dtime;
	desc.m_Direction = { 0 ,0};
	desc.m_Position = { 500,500 };
	desc.m_Speed = 2;
	desc.ratio = 15;
	desc.arrive.impetu = 10;
	desc.arrive.objetive = MousePosition;
	desc.arrive.ratio = 10;
	//boid.Init(desc);
	/*BoidDescriptor descForEvade;
	descForEvade.m_Direction = { 0,0 };
	descForEvade.m_Position = { 600,600 };
	descForEvade.m_Speed = 1;
	descForEvade.shapeColor = { 255,0,0,255 };
	descForEvade.evade.impetu = 10;
	descForEvade.evade.objetive = &boid;
	descForEvade.evade.timeProyection = 5;
	BoidDescriptor descForPersu;
	descForPersu.m_Direction = { 0,0 };
	descForPersu.m_Position = { 600,600 };
	descForPersu.m_Speed = 1;
	descForPersu.shapeColor = { 255,0,0,255 };
	descForPersu.persu.impetu = 10;
	descForPersu.persu.objetive = &boid;
	descForPersu.persu.timeProyection = 15;
	PersuOrEvadeboid.Init(descForPersu);
	return;*/
	boids;
	BoidDescriptor wanderRandDesc;
	wanderRandDesc.wander.type = TypeWander::WanderTypeRandom;
	wanderRandDesc.wander.limitsX = CD::CDVector2(0,900);
	wanderRandDesc.wander.limitsY = CD::CDVector2(0,900);
	wanderRandDesc.wander.impetu = 10;
	wanderRandDesc.globalTime= dtime;
	wanderRandDesc.ratio= 4;
	wanderRandDesc.m_Speed = 1;
	wanderRandDesc.m_Position = CD::CDVector2(400, 400);
	wanderRandDesc.shapeColor = { 255, 0, 0, 255 };
	BoidDescriptor wanderTimeDesc;
	wanderTimeDesc.wander.type = TypeWander::wanderTypeTime;
	wanderTimeDesc.wander.limitsX = CD::CDVector2(0, 900);
	wanderTimeDesc.wander.limitsY = CD::CDVector2(0, 900);
	wanderTimeDesc.wander.impetu = 10;
	wanderTimeDesc.wander.timeToNextPoint = 3;
	wanderTimeDesc.globalTime = dtime;
	wanderTimeDesc.ratio = 4;
	wanderTimeDesc.m_Speed = 1;
	wanderTimeDesc.m_Position = CD::CDVector2(200, 200);
	wanderTimeDesc.shapeColor = { 0, 255, 0, 255 };
	BoidDescriptor wanderDesc;
	wanderDesc.wander.type = TypeWander::WanderTypeVision;
	wanderDesc.wander.ratio=20;
	wanderDesc.wander.openingAngleInDegrees=90;
	wanderDesc.wander.impetu=10;
	wanderDesc.wander.DistoToPointProyection=10;
	wanderDesc.globalTime = dtime;
	wanderDesc.ratio = 4;
	wanderDesc.m_Speed = 1;
	wanderDesc.m_Position = CD::CDVector2(500, 500);
	wanderDesc.shapeColor = { 0, 0, 255, 255 };
	//wanderRan.Init(wanderRandDesc);
	//boids.push_back(wanderRan);
	//wanderTime.Init(wanderTimeDesc);
	//boids.push_back(wanderTime);
	//wader.Init(wanderDesc);
	//boids.push_back(wader);
	BoidDescriptor folloPathDes;
	folloPathDes.followPath.IndexPoint = 0;
	folloPathDes.followPath.impetu = 10;
	folloPathDes.followPath.Points = path;
	folloPathDes.followPath.ratio = 15;
	folloPathDes.globalTime = dtime;
	folloPathDes.ratio = 4;
	folloPathDes.m_Speed = 1;
	folloPathDes.m_Position = CD::CDVector2(500, 500);
	folloPathDes.shapeColor = { 0, 0, 255, 255 };
	//pathFollower.Init(folloPathDes);
	//boids.push_back(pathFollower);
	BoidDescriptor patrolDesc;
	patrolDesc.globalTime = dtime;
	patrolDesc.ratio = 4;
	patrolDesc.m_Speed = 2;
	patrolDesc.m_Position = CD::CDVector2(500, 500);
	patrolDesc.shapeColor = { 0, 0, 255, 255 };
	patrolDesc.patrol.indexPath = 0;
	patrolDesc.patrol.Points = path;
	patrolDesc.patrol.impetu = 10;
	patrolDesc.patrol.Ratio = 15;
	patrolDesc.patrol.type = PatrolTypeInverted;
	patrolDesc.patrol.timeToStay = 3;
	//patroler.Init(patrolDesc);
	//boids->push_back(&patroler);
	BoidDescriptor flockingDesc;
	flockingDesc.globalTime = dtime;
	flockingDesc.ratio = 10;
	flockingDesc.m_Speed = 1;
	flockingDesc.m_Position = CD::CDVector2(500, 500);
	flockingDesc.shapeColor = { 0, 0, 255, 255 };
	flockingDesc.flocking.Boids = boids;
	flockingDesc.flocking.impetu = 10;
	flockingDesc.flocking.ratioVision = 30;
	//boid.Init(flockingDesc);
	//boids->push_back(&boid);
	//
	//flockingDesc.m_Position = CD::CDVector2(520, 500);
	//flockingDesc.shapeColor = { 255, 0, 0, 255 };
	//wanderRan.Init(flockingDesc);
	//boids->push_back(&wanderRan);
	//
	//flockingDesc.m_Position = CD::CDVector2(500, 520);
	//flockingDesc.shapeColor = { 0, 255, 0, 255 };
	//wanderTime.Init(flockingDesc);
	//boids->push_back(&wanderTime);
	//
	//flockingDesc.m_Position = CD::CDVector2(520, 520);
	//flockingDesc.shapeColor = { 255, 0, 255, 255 };
	//wader.Init(flockingDesc);
	//boids->push_back(&wader);
	//
	//flockingDesc.m_Position = CD::CDVector2(540, 500);
	//flockingDesc.shapeColor = { 0, 255, 255, 255 };
	//pathFollower.Init(flockingDesc);
	//boids->push_back(&pathFollower);
	//
	//flockingDesc.m_Position = CD::CDVector2(500, 540);
	//flockingDesc.shapeColor = { 255, 255, 0, 255 };
	//patroler.Init(flockingDesc);
	//boids->push_back(&patroler);

	BoidDescriptor FollowTheLeaderDesc;
	FollowTheLeaderDesc.globalTime = dtime;
	FollowTheLeaderDesc.ratio = 10;
	FollowTheLeaderDesc.m_Speed = 1;
	FollowTheLeaderDesc.m_Position = CD::CDVector2(500, 500);
	FollowTheLeaderDesc.shapeColor = { 0, 0, 255, 255 };
	FollowTheLeaderDesc.followLeader.Boids = boids;
	FollowTheLeaderDesc.followLeader.impetu = 10;
	FollowTheLeaderDesc.followLeader.ratioVision = 30;
	FollowTheLeaderDesc.followLeader.distToLeader = 50;
	FollowTheLeaderDesc.followLeader.Leader = &boid;

	boid.Init(desc);
	boids->push_back(&boid);

	FollowTheLeaderDesc.m_Position = CD::CDVector2(520, 500);
	FollowTheLeaderDesc.shapeColor = { 255, 0, 0, 255 };
	wanderRan.Init(FollowTheLeaderDesc);
	boids->push_back(&wanderRan);

	FollowTheLeaderDesc.m_Position = CD::CDVector2(500, 520);
	FollowTheLeaderDesc.shapeColor = { 0, 255, 0, 255 };
	wanderTime.Init(FollowTheLeaderDesc);
	boids->push_back(&wanderTime);

	FollowTheLeaderDesc.m_Position = CD::CDVector2(520, 520);
	FollowTheLeaderDesc.shapeColor = { 255, 0, 255, 255 };
	wader.Init(FollowTheLeaderDesc);
	boids->push_back(&wader);

	FollowTheLeaderDesc.m_Position = CD::CDVector2(540, 500);
	FollowTheLeaderDesc.shapeColor = { 0, 255, 255, 255 };
	pathFollower.Init(FollowTheLeaderDesc);
	boids->push_back(&pathFollower);

	FollowTheLeaderDesc.m_Position = CD::CDVector2(500, 540);
	FollowTheLeaderDesc.shapeColor = { 255, 255, 0, 255 };
	patroler.Init(FollowTheLeaderDesc);
	boids->push_back(&patroler);
}

void Update()
{
	sf::Vector2i Mpos=sf::Mouse::getPosition(*wind);
	sf::Vector2f cordPos=wind->mapPixelToCoords(Mpos);
	MousePosition->x = cordPos.x;
	MousePosition->y = cordPos.y;
	//boid.Update();
	//PersuOrEvadeboid.Update();
	for(int i=0; i< boids->size();i++)
	{
		boids[0][i]->Update();
	}
}

void Render()
{
	//boid.Render(*wind);
	//PersuOrEvadeboid.Render(*wind);
	for (int i = 0; i < boids->size(); i++)
	{
		boids[0][i]->Render(*wind);
	}
}

void Input()
{
}

void Delete()
{
	//boid.Delete();
	delete dtime;
	for (int i = 0; i < boids->size(); i++)
	{
		boids[0][i]->Delete();
		//delete boids[0][i];
	}
	delete boids;
	delete path;
	//PersuOrEvadeboid.Delete();
}
