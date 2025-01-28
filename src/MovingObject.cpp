#include "MovingObject.h"

MovingObject::MovingObject(sf::RenderWindow& window, sf::Vector2f position) : GameObject(window, position){}

MovingObject::MovingObject()
{
	m_direction = sf::Vector2f(0, 0);
}

void MovingObject::move(sf::Time deltaTime)
{
	if (m_direction != sf::Vector2f(0, 0) && m_movementTimer.getElapsedTime().asSeconds() > m_maxMovementTime) 
	{
		m_direction = sf::Vector2f(0, 0); // Stop movement after 5 seconds
		return;
	}
	const auto speedPerSecond = (float)(m_tileSize);
	moveSprite(m_direction * speedPerSecond * deltaTime.asSeconds());
}

void MovingObject::setDirection(sf::Keyboard::Key key)
{
	switch (key)
	{
	case sf::Keyboard::Space:
		m_direction = sf::Vector2f(0, 0);
		break;
	case sf::Keyboard::Key::Left:
		m_direction = sf::Vector2f(-1, 0);
		break;
	case sf::Keyboard::Key::Right:
		m_direction = sf::Vector2f(1, 0);
		break;
	case sf::Keyboard::Key::Up:
		m_direction = sf::Vector2f(0, -1);
		break;
	case sf::Keyboard::Key::Down:
		m_direction = sf::Vector2f(0, 1);
		break;
	default:
		break;
	}

	// Reset the movement timer when a new direction is set
	if (m_direction != sf::Vector2f(0, 0)) 
	{
		m_movementTimer.restart(); // Restart the timer
	}
}