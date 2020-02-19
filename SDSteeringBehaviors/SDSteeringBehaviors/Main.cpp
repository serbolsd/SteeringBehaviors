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
CD::CDVector2 *MousePosition;
std::vector<Boid> boids;
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
	/*BoidDescriptor desc;
	desc.m_Direction = { 0 ,0};
	desc.m_Position = { 300,300 };
	desc.m_Speed = 3;
	desc.arrive.impetu = 10;
	desc.arrive.objetive = MousePosition;
	desc.arrive.ratio = 10;
	boid.Init(desc);
	BoidDescriptor descForEvade;
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
	wader.Init(wanderDesc);
	boids.push_back(wader);
}

void Update()
{
	sf::Vector2i Mpos=sf::Mouse::getPosition(*wind);
	sf::Vector2f cordPos=wind->mapPixelToCoords(Mpos);
	MousePosition->x = cordPos.x;
	MousePosition->y = cordPos.y;
	//boid.Update();
	//PersuOrEvadeboid.Update();
	for(int i=0; i< boids.size();i++)
	{
		boids[i].Update();
	}
}

void Render()
{
	//boid.Render(*wind);
	//PersuOrEvadeboid.Render(*wind);
	for (int i = 0; i < boids.size(); i++)
	{
		boids[i].Render(*wind);
	}
}

void Input()
{
}

void Delete()
{
	//boid.Delete();
	delete dtime;
	for (int i = 0; i < boids.size(); i++)
	{
		boids[i].Delete();
	}
	//PersuOrEvadeboid.Delete();
}
