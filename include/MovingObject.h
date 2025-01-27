#pragma once
#include "GameObject.h"
#include <vector>


class MovingObject : public GameObject 
{
public:
	MovingObject();
	MovingObject(sf::RenderWindow& window, sf::Vector2f position);
	virtual void move(sf::Time deltaTime);
	//virtual bool canMove(sf::Vector2f newPosition, std::vector<std::vector<GameObject*>>* m_gameObjects);
	void setDirection(sf::Keyboard::Key key);

private:
	sf::Vector2f m_direction;
};