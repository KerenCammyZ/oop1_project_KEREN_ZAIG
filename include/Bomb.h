#pragma once
#include "MovingObject.h"

class Bomb : public MovingObject 
{
public:
	Bomb();
	Bomb(sf::RenderWindow& window, sf::Vector2f position);
	void move(sf::Time deltaTime, const std::vector<std::vector<GameObject*>>& m_board, Player& player) override;
	//void explode(const std::vector<std::vector<GameObject*>>& m_board, Player& player);
	void setAlive(bool flag);
	void countdown();
	int getCount();
private:
	sf::Clock m_timer;
	bool m_alive = false;
};