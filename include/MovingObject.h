#pragma once
#include "GameObject.h"
#include <vector>


class MovingObject : public GameObject 
{
public:
	MovingObject();
	MovingObject(sf::RenderWindow& window, sf::Vector2f position);
	virtual void move(sf::Time deltaTime, const std::vector<std::vector<GameObject*>>& m_board);
	void setDirection(sf::Keyboard::Key key);
	void moveSprite(const sf::Vector2f& offset);

private:
	sf::Vector2f m_direction;
	sf::Clock m_movementTimer;
	const float m_maxMovementTime = 0.5f;

};