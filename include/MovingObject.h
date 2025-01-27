#pragma once
#include "GameObject.h"
#include <vector>


class MovingObject : public GameObject 
{
public:
	MovingObject();
	MovingObject(sf::RenderWindow& window, sf::Vector2f position);
	virtual void move(sf::Keyboard::Key key, std::vector<std::vector<GameObject*>>* m_gameObjects);
	virtual bool canMove(sf::Vector2f newPosition, std::vector<std::vector<GameObject*>>* m_gameObjects);

private:
	sf::Vector2f m_currentPosition;
	sf::Vector2f m_newPosition;

};