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

void Bomb::explode(std::vector<std::vector<GameObject*>>& board, Player& player)
{
	/*
	//std::cout << " Bomb exploded! \n";

	for (int i = 0; i < board.size(); i++)
	{
		GameObject* obj = board[i][j];

		if (obj == nullptr) continue; // Safety check

		//  Check if the object is a Rock
		Rock* rock = dynamic_cast<Rock*>(obj);
		if (rock && checkCollision(this, rock))
		{
			std::cout << "🪨 Rock destroyed!\n";
			delete board[i];
			board.erase(board.begin() + i);
			i--; // Adjust index after erasing
			continue;
		}

		//  Check if the object is a Wall (Walls should NOT be destroyed)
		Wall* wall = dynamic_cast<Wall*>(obj);
		if (wall && checkCollision(this, wall))
		{
			std::cout << "🧱 Bomb hit a wall! Nothing happens.\n";
			continue;
		}
		
	}

	//  Check if Player is hit
	if (checkCollision(this, player))
	{
		//std::cout << " Player hit! Losing life.\n";
		player.lostLife();
	}
	}
	*/
}



void Bomb::setAlive(bool flag)
{
	m_alive = flag;
}

int Bomb::getCount()
{
	return m_timer.getElapsedTime().asSeconds();
}
