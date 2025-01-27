#pragma once
#include "GameObject.h"

class MjovingObect : public GameObject 
{
public:
	virtual void move(sf::Keyboard::Key key, std::vector<std::vector<GameObject*>>* m_gameObjects);
	virtual bool canMove(sf::Vector2f newPosition, std::vector<std::vector<GameObject*>>* m_gameObjects);

private:
	sf::Vector2f m_currentPosition;
	sf::Vector2f m_newPosition;

};