#include "Player.h"

Player::Player()
{
	if (!(m_playerTexture.loadFromFile("player.png") && m_wallTexture.loadFromFile("wall.png")
		&& m_doorTexture.loadFromFile("door.png") && m_rockTexture.loadFromFile("rock.png")))
	{
		std::cerr << "Failed to load one or more textures.\n";
		return;
	}
	m_playerSprite.setTexture(m_playerTexture);
	m_playerSprite.setPosition(m_tileSize, m_tileSize + m_toolbarHeight);
}

void Player::drawPlayer(sf::RenderWindow& window)
{
	window.draw(m_playerSprite);
}

void Player::movePlayer(int x, int y, Board &board)
{
	 
	//check for collision
	sf::Vector2f currentPosition = m_playerSprite.getPosition();
	sf::Vector2f newPosition = currentPosition + sf::Vector2f(x * 69, y * 69);

	/*if ((newPosition == board.getTilePosition(x, y) && board.getTexture(x,y) == m_wallTexture)) {

	}*/

	m_playerSprite.move(x * m_tileSize, y * m_tileSize);
}
