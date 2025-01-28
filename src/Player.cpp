#include "Player.h"

Player::Player(sf::RenderWindow& window, sf::Vector2f position)
    : MovingObject(window, position), m_lives(3), m_score(0), m_alive(true) {
    setPosition(position);    // Set initial position
}

Player::Player() : MovingObject(), m_lives(3), m_score(0), m_alive(true) {
	setPosition(sf::Vector2f(getTileSize(), getTileSize()));
}