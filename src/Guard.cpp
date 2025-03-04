#include <cstdlib>
#include <ctime>
#include <memory>
#include "Guard.h"
#include "Player.h"

Guard::Guard(sf::RenderWindow& window, sf::Vector2f position)
	: MovingObject(window, position)
{
	m_alive = true;
    m_type = GUARD;
}

sf::Vector2f Guard::findPlayerDirection(const sf::Vector2f& playerPosition)
{
	// Calculate the direction vector in 2D
	sf::Vector2f direction = playerPosition - m_position;

	// Normalize the direction vector
	float magnitude = std::sqrt(direction.x * direction.x + direction.y * direction.y);

	if (magnitude != 0.f) {
		direction /= magnitude; // Normalize to a unit vector
	}

	return direction; // Return the normalized direction as a 2D vector
	
}

void Guard::changeDirection(const Player player)
{
    int randomChoice = rand() % 2;  // Random number between 0 and 1

    switch (randomChoice) {
    case 0: //follow player
		m_currentDirection = findPlayerDirection(player.getPosition());
		break;
	case 1: // Random direction
		m_currentDirection = sf::Vector2f(rand() % 3 - 1, rand() % 3 - 1);
		break;
    }
}

void Guard::draw() const
{
    if (m_alive)
        m_window->draw(m_sprite);
}

bool Guard::isAlive()
{
    return m_alive;
}

void Guard::setDead()
{
    m_alive = false;
}

void Guard::setFrozen(bool freeze)
{
    m_frozen = freeze;
}

void Guard::move(sf::Time deltaTime, std::vector<std::vector<std::unique_ptr<GameObject>>> &m_board, Player &player)
{
    //dont move if frozen
    if (m_frozen)
        return;

    const auto speedPerSecond = static_cast<float>(m_tileSize);

    // Check if it's time to change direction
    if (m_directionChangeClock.getElapsedTime().asSeconds() > 6) { 
        changeDirection(player);  //change direction after 5 seconds
        m_directionChangeClock.restart();  // Reset the clock
    }

    // Calculate movement based on the current direction
    sf::Vector2f movement = m_currentDirection * speedPerSecond * deltaTime.asSeconds();

    // Predict the new position of the sprite
    sf::FloatRect predictedBounds = m_sprite.getGlobalBounds();
    predictedBounds.left += movement.x;
    predictedBounds.top += movement.y;

    bool canMove = true;

    // Check for collisions
    for (const auto& row : m_board) 
    {
        for (const auto& obj : row) 
        {
            if (obj) {
                sf::FloatRect objectBounds = obj->getBounds();

                // Check for collision with the object
                if (objectBounds.intersects(predictedBounds)) {
                    if (obj->getType() == WALL || obj->getType() == ROCK) 
                    {
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
                        canMove = false;
                    }
                }
            }
        }
    }


    // If no collision, move the guard
    if (canMove) {
        moveSprite(movement);
    }

    //if collision with player, lose life
    if (m_sprite.getGlobalBounds().intersects(player.getBounds()))
        player.lostLife();
}