#include "Player.h"

Player::Player(sf::RenderWindow& window, sf::Vector2f position)
    : MovingObject(window, position), m_lives(3), m_score(0), m_alive(true) {
    setPosition(position);    // Set initial position
    m_type = "player";
}

Player::Player() : MovingObject(), m_lives(3), m_score(0), m_alive(true) {
	setPosition(sf::Vector2f(m_tileSize, m_tileSize));
	m_type = "player";
}

void Player::lostLife()
{
    m_lives--;
}
