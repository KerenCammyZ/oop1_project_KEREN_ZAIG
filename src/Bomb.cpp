#include "Bomb.h"
#include "Player.h"

Bomb::Bomb() : MovingObject()
{
	m_alive = false;
	m_timer.restart();
}

Bomb::Bomb(sf::RenderWindow& window, sf::Vector2f position)
	: MovingObject(window, position)
{
	m_alive = false;
	m_timer.restart();
	setPosition(position);
}

void Bomb::move(sf::Time deltaTime, std::vector<std::vector<GameObject*>>& m_board, Player& player)
{
	if (m_timer.getElapsedTime().asSeconds() == 0)
	{
		explode(m_board, player);
		setAlive(false);
	}
	else
		return;
}

void Bomb::explode(std::vector<std::vector<GameObject*>>& m_board, Player& player)
{
	int centerX = getSprite().getPosition().x;
	int centerY = getSprite().getPosition().y;

	std::string center = m_board[centerX][centerY]->getType();
	std::string left = m_board[centerX - 1][centerY]->getType();
	std::string right = m_board[centerX + 1][centerY]->getType();
	std::string up = m_board[centerX][centerY + 1]->getType();
	std::string down = m_board[centerX][centerY - 1]->getType();

	if (center == "player" || left == "player" || right == "player" || up == "player" || down == "player")
	{
		player.lostLife();
	}
	if (center == "guard" || left == "guard" || right == "guard" || up == "guard" || down == "guard")
	{
		//make guard dissapear here
	}
	if (center == "rock" || left == "rock" || right == "rock" || up == "rock" || down == "rock")
	{
		//make rock dissapear here
		if (center == "rock")
		{
			delete m_board[centerX][centerY];
			m_board[centerX][centerY] = nullptr;
		}
		if (left == "rock")
		{
			delete m_board[centerX - 1][centerY];
			m_board[centerX - 1][centerY] = nullptr;
		}
		if (right == "rock")
		{
			delete m_board[centerX + 1][centerY];
			m_board[centerX + 1][centerY] = nullptr;
		}
		if (up == "rock")
		{
			delete m_board[centerX][centerY + 1];
			m_board[centerX][centerY + 1] = nullptr;
		}
		if (down == "rock")
		{
			delete m_board[centerX][centerY - 1];
			m_board[centerX][centerY - 1] = nullptr;
		}
	}
	
}



void Bomb::setAlive(bool flag)
{
	m_alive = flag;
}

int Bomb::getCount()
{
	return m_timer.getElapsedTime().asSeconds();
}
