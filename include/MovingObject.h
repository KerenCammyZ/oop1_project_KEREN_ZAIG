#pragma once
#include "GameObject.h"

class MovingObject : public GameObject 
{
public:
	virtual void move(sf::Keyboard::Key key, sf::RenderWindow window);
private:

};