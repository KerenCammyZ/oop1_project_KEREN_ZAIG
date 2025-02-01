#include "MovingObject.h"
#include "Player.h"
#include "Door.h"

MovingObject::MovingObject(sf::RenderWindow& window, sf::Vector2f position) : GameObject(position.x, position.y, UNKNOWN, window){}

MovingObject::MovingObject()
{
	m_direction = sf::Vector2f(0, 0);
}


void MovingObject::moveSprite(const sf::Vector2f& offset)
{
	m_sprite.move(offset);
}

void MovingObject::move(sf::Time deltaTime, std::vector<std::vector<GameObject*>>& m_board, Player &player)
{
    const auto speedPerSecond = static_cast<float>(m_tileSize);

    // Calculate intended movement
    sf::Vector2f movement = m_direction * speedPerSecond * deltaTime.asSeconds();

    // Predict the new position of the sprite
    sf::FloatRect predictedBounds = m_sprite.getGlobalBounds();
    predictedBounds.left += movement.x;
    predictedBounds.top += movement.y;

    // Flag to determine if movement is allowed
    bool canMove = true;

    // Check for collisions
    for (const auto& row : m_board) {
        for (const auto& obj : row) {
            if (obj) {
                sf::FloatRect objectBounds = obj->getBounds();

                // Check for collision with the object
                if (objectBounds.intersects(predictedBounds)) {
                    if (obj->getType() == WALL || obj->getType() == ROCK) {
                        // Resolve the collision by adjusting the movement
                        sf::FloatRect intersection;
                        if (predictedBounds.intersects(objectBounds, intersection)) {
                            // Determine the smallest overlap to resolve the collision
                            if (intersection.width < intersection.height) {
                                // Horizontal collision
                                movement.x = (predictedBounds.left < objectBounds.left ? -intersection.width : intersection.width);
                                movement.y = 0; // Disable vertical movement
                            }
                            else {
                                // Vertical collision
                                movement.y = (predictedBounds.top < objectBounds.top ? -intersection.height : intersection.height);
                                movement.x = 0; // Disable horizontal movement
                            }
                        }
                        // Block further checks for this object
                        canMove = false;
                    }
                    else if (obj->getType() == DOOR) {
                        // If the object is a Door, set its m_passed attribute to true
                        Door* door = dynamic_cast<Door*>(obj);
                        if (door) {
                            door->setPassed(true);
                        }
                        // Allow movement through the door
                        canMove = true;
                    }
                }
            }
        }
    }

    // Apply the resolved movement if no collision blocks it
    if (canMove || movement != sf::Vector2f(0, 0)) {
        moveSprite(movement);
        m_position = movement;
    }

    // Reset direction if movement is blocked for too long
    if (m_direction != sf::Vector2f(0, 0) && m_movementTimer.getElapsedTime().asSeconds() > m_maxMovementTime) {
        m_direction = sf::Vector2f(0, 0);
    }
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