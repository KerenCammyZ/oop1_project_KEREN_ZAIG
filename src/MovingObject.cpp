#include "MovingObject.h"

MovingObject::MovingObject(sf::RenderWindow& window, sf::Vector2f position) : GameObject(window, position){}

MovingObject::MovingObject()
{
	m_direction = sf::Vector2f(0, 0);
}

void MovingObject::move(sf::Time deltaTime)
{
	const auto speedPerSecond = 40.f;
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
}

//bool MovingObject::canMove(sf::Vector2f newPosition, std::vector<std::vector<GameObject*>>* m_gameObjects)
//{
//	// Calculate row and column based on the new position
//	int row = static_cast<int>(newPosition.y / getTileSize());
//	int col = static_cast<int>(newPosition.x / getTileSize());
//
//	// Check if the position is out of bounds
//	if (row < 0 || row >= m_gameObjects->size() || col < 0 || col >= (*m_gameObjects)[row].size()) {
//		return false; // Out of bounds
//	}
//
//	// Check if the object at the new position is null
//	GameObject* targetObject = (*m_gameObjects)[row][col];
//	if (!targetObject) {
//		return true; // Empty space
//	}
//
//	// Check the name of the object
//	std::string newPositionName = targetObject->getName();
//	if (newPositionName == "Guard.png" || newPositionName == "Wall.png") {
//		return false; // Cannot move into guards or walls
//	}
//
//	return true; // All other tiles are passable	
//}