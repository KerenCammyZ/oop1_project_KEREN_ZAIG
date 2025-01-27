#include "MovingObject.h"

MovingObject::MovingObject(sf::RenderWindow& window, sf::Vector2f position) : GameObject(window, position){}

MovingObject::MovingObject() : m_currentPosition(0, 0), m_newPosition(0, 0){}

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
	// Calculate row and column based on the new position
	int row = static_cast<int>(newPosition.y / getTileSize());
	int col = static_cast<int>(newPosition.x / getTileSize());

	// Check if the position is out of bounds
	if (row < 0 || row >= m_gameObjects->size() || col < 0 || col >= (*m_gameObjects)[row].size()) {
		return false; // Out of bounds
	}

	// Check if the object at the new position is null
	GameObject* targetObject = (*m_gameObjects)[row][col];
	if (!targetObject) {
		return true; // Empty space
	}

	// Check the name of the object
	std::string newPositionName = targetObject->getName();
	if (newPositionName == "Guard.png" || newPositionName == "Wall.png") {
		return false; // Cannot move into guards or walls
	}

	return true; // All other tiles are passable	
}