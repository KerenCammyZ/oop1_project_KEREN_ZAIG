#include "MovingObject.h"

void MovingObject::move(sf::Keyboard::Key key, std::vector<std::vector<GameObject*>>* m_gameObjects)
{
	m_currentPosition = getPosition();
	m_newPosition = m_currentPosition;

	switch (key)
	{
	case sf::Keyboard::Up:
		m_newPosition.y -= getTileSize();
		break;
	case sf::Keyboard::Down:
		m_newPosition.y += getTileSize();
		break;
	case sf::Keyboard::Left:
		m_newPosition.x -= getTileSize();
		break;
	case sf::Keyboard::Right:
		m_newPosition.x += getTileSize();
		break;
	}

	if (canMove(m_newPosition, m_gameObjects))
	{
		setPosition(m_newPosition);
	}
}

bool MovingObject::canMove(sf::Vector2f newPosition, std::vector<std::vector<GameObject*>>* m_gameObjects)
{
	std::string newPositionName = m_gameObjects->at(newPosition.y / getTileSize()).at(newPosition.x / getTileSize())->getName();
	if (newPositionName.compare("Guard.png") == 0)
	{
		return false;
	}
	else if (newPositionName.compare("Wall.png") == 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}