#include <playerInputs.h>
#include <SFML/Graphics.hpp>
#include <CDVectors.h>
#include <Boid.h>

PlayerInput::PlayerInput()
{
}

PlayerInput::~PlayerInput()
{
	
}

void PlayerInput::onUpdate(Boid& _player)
{
	CD::CDVector2 direction;
	if (
		(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
		)
	{
		direction.y -= 1;
	}
	if(
		(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
	)
	{
		direction.y += 1;

	}
	if(
		(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
	)
	{
		direction.x -= 1;
	}
	if(
		(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
	)
	{
		direction.x += 1;
	}
	_player.newDirection += direction;
}
