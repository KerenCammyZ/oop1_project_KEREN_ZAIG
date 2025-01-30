#pragma once
#include "MovingObject.h"

class Bomb : public MovingObject 
{
public:
	Bomb();
	Bomb(sf::RenderWindow& window, sf::Vector2f position);
	void move(sf::Time deltaTime, std::vector<std::vector<GameObject*>>& m_board, Player& player) override;
	void explode(std::vector<std::vector<GameObject*>>& m_board, Player& player);
	void setAlive(bool flag);

	int getCount();
private:
	sf::Clock m_timer;
	bool m_alive = false;
};