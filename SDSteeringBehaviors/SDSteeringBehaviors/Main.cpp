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
Boid PersuOrEvadeboid;
CD::CDVector2 *MousePosition;
int main()
{
	//sum();
	wind= new sf::RenderWindow(sf::VideoMode(900, 900), "window");
	Init();
	wind->setFramerateLimit(60);
	sf::Event event;
	while (wind->isOpen())
	{
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
	}
	Delete();
	return 0;
}

void Init()
{
	MousePosition = new CD::CDVector2;
	BoidDescriptor desc;
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
	return;
}

void Update()
{
	sf::Vector2i Mpos=sf::Mouse::getPosition(*wind);
	sf::Vector2f cordPos=wind->mapPixelToCoords(Mpos);
	MousePosition->x = cordPos.x;
	MousePosition->y = cordPos.y;
	boid.Update();
	PersuOrEvadeboid.Update();
}

void Render()
{
	boid.Render(*wind);
	PersuOrEvadeboid.Render(*wind);
}

void Input()
{
}

void Delete()
{
	boid.Delete();
	//PersuOrEvadeboid.Delete();
}
