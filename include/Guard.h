#pragma once
#include "MovingObject.h"

class Guard : public MovingObject
{
public:
	Guard(sf::RenderWindow& window, sf::Vector2f position);
	void move(sf::Time deltaTime, std::vector<std::vector<GameObject*>>& m_board, Player &player) override;
	sf::Vector2f findPlayerDirection(const sf::Vector2f& playerPosition);
	void changeDirection(const Player player);
	void draw() const override;
	bool isAlive();
	void setDead();
	void setFrozen(bool freeze);
private:
	bool m_alive, m_frozen = false;
	sf::Clock m_directionChangeClock;  // Timer to track the direction change
	sf::Vector2f m_currentDirection;   // Current direction of the guard
};