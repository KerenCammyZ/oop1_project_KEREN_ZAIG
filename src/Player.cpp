#include "Player.h"

Player::Player(sf::RenderWindow& window, sf::Vector2f position)
    : MovingObject(window, position), m_lives(3), m_score(0), m_alive(true) {
    setTexture("player.png"); // Load and assign texture
    setPosition(position);    // Set initial position
}

Player::Player() : MovingObject(), m_lives(3), m_score(0), m_alive(true) {
    sf::Texture playerTexture;
    playerTexture.loadFromFile("player.png");
    setTexture("player.png");
    setSpriteTexture(playerTexture);
	setPosition(sf::Vector2f(20, 20));
}
