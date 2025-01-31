#include "Player.h"

Player::Player(sf::RenderWindow& window, sf::Vector2f position)
    : MovingObject(window, position), m_lives(3), m_score(0), m_alive(true) {
    setPosition(position);    // Set initial position
    m_type = PLAYER;
}

Player::Player() : MovingObject(), m_lives(3), m_score(0), m_alive(true) {
	setPosition(sf::Vector2f(m_tileSize, m_tileSize));
	m_type = PLAYER;
}

void Player::lostLife()
{
    if (m_lives > 0)
    {
        m_lives--;
        respawn();
    }
    if (m_lives == 0) //game over
    {
        m_alive = false;
        return;
    }
}

void Player::respawn()
{
    setPosition(sf::Vector2f(m_tileSize, m_tileSize));
    setDirection(sf::Keyboard::Space);
}
