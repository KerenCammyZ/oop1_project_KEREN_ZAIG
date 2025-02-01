#pragma once
#include "MovingObject.h"

class Player : public MovingObject{
public:
	Player(sf::RenderWindow& window, sf::Vector2f position);
	Player();	
	void lostLife();
	int getLives() const { return m_lives; }
	void respawn();
private:
	int m_lives = 3;
};

