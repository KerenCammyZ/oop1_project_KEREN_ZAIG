#include <cstdlib>
#include <ctime>
#include "Guard.h"

Guard::Guard(sf::RenderWindow& window, sf::Vector2f position)
	: MovingObject(window, position)
{
	m_alive = true;
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

void Guard::changeDirection()
{
    // Generate a random direction (up, down, left, or right)
    int randomChoice = rand() % 4;  // Random number between 0 and 3

    switch (randomChoice) {
    case 0: m_currentDirection = sf::Vector2f(0, -1); break;  // Up
    case 1: m_currentDirection = sf::Vector2f(0, 1); break;   // Down
    case 2: m_currentDirection = sf::Vector2f(-1, 0); break;  // Left
    case 3: m_currentDirection = sf::Vector2f(1, 0); break;   // Right
    }
}

void Guard::move(sf::Time deltaTime, const std::vector<std::vector<GameObject*>>& m_board)
{
    const auto speedPerSecond = static_cast<float>(m_tileSize);

    // Check if it's time to change direction
    if (m_directionChangeClock.getElapsedTime().asSeconds() > rand() % 5 + 2) { // Random time between 2 and 6 seconds
        changeDirection();  // Change direction after random time
        m_directionChangeClock.restart();  // Reset the clock
    }

    // Calculate movement based on the current random direction
    sf::Vector2f movement = m_currentDirection * speedPerSecond * deltaTime.asSeconds();

    // Predict the new position of the sprite
    sf::FloatRect predictedBounds = m_sprite.getGlobalBounds();
    predictedBounds.left += movement.x;
    predictedBounds.top += movement.y;

    bool canMove = true;

    // Check for collisions
    for (const auto& row : m_board) {
        for (const auto& obj : row) {
            if (obj) {
                sf::FloatRect objectBounds = obj->getBounds();

                // Check for collision with the object
                if (objectBounds.intersects(predictedBounds)) {
                    if (obj->getType() == "wall" || obj->getType() == "rock") {
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
}

