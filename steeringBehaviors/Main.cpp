#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

int main()
{
	sf::RenderWindow render(sf::VideoMode(500,500),"la ventana");

	sf::Event _event;
	while (render.isOpen())
	{
		while (render.pollEvent(_event))
		{
			if (_event.type == sf::Event::Closed)
				render.close();
			if (_event.key.code == sf::Keyboard::Escape)
			{
				render.close();
			}

		}
		render.clear(sf::Color(100, 0, 100, 255));
		render.display();
	}
	return 0;
}