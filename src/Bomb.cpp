#include "Bomb.h"

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
}

void Bomb::move(sf::Time deltaTime, const std::vector<std::vector<GameObject*>>& m_board, Player& player)
{
	if (m_timer.getElapsedTime().asSeconds() < 4)
		countdown();
	else if (m_timer.getElapsedTime().asSeconds() == 0)
	{
		//explode(m_board, player);
		setAlive(false);
	}
	else
		return;
}

void Bomb::setAlive(bool flag)
{
	m_alive = flag;
}

void Bomb::countdown()
{
	int timer = m_timer.getElapsedTime().asSeconds();
		switch (timer) 
		{
		case 4:
			//setTexture()
			break;
		case 3:
			break;
		case 2:
			break;
		case 1:
			break;
		default:
			break;
		}
}

int Bomb::getCount()
{
	return m_timer.getElapsedTime().asSeconds();
}
