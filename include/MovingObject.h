#pragma once
#include "GameObject.h"

class MjovingObect : public GameObject 
{
public:
	virtual void move(sf::Keyboard::Key key, sf::RenderWindow window);
private:

};