#pragma once
#include "MovingObject.h"

class Bomb : public MovingObject 
{
public:
	void move(sf::Time deltaTime, const std::vector<std::vector<GameObject*>>& m_board, Player& player) override;
	void Explode();

private:
	sf::Clock m_timer;

};