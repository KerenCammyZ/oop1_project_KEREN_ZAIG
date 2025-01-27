#pragma once
#include "MovingObject.h"

class Player : public MovingObject{
public:
	Player(sf::RenderWindow& window, sf::Vector2f position);
	Player();	
private:
	int m_lives = 3;
	int m_score = 0;
	bool m_alive = true;
};

