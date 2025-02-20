#pragma once
#include "GameObject.h"
#include <vector>
class Player;

class MovingObject : public GameObject 
{
public:
	MovingObject(sf::RenderWindow& window, sf::Vector2f position);
	MovingObject();
	virtual void move(sf::Time deltaTime, std::vector<std::vector<std::unique_ptr<GameObject>>> &m_board, Player &player);
	void setDirection(sf::Keyboard::Key key);
	void moveSprite(const sf::Vector2f& offset);
private:
	sf::Vector2f m_direction;
	sf::Clock m_movementTimer;
	const float m_maxMovementTime = 0.5f;

};