#pragma once
#include "GameObject.h"
#include <vector>


class MovingObject : public GameObject 
{
public:
	MovingObject();
	MovingObject(sf::RenderWindow& window, sf::Vector2f position);
	virtual void move(sf::Time deltaTime);
	void setDirection(sf::Keyboard::Key key);
	

private:
	sf::Vector2f m_direction;
	sf::Clock m_movementTimer;
	const float m_maxMovementTime = 2.0f;
};