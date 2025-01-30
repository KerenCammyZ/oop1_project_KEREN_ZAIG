#pragma once
#include "StaticObject.h"
#include <SFML/Graphics.hpp>

class Bomb : public StaticObject 
{
public:
	Bomb(sf::RenderWindow& window, float x, float y);
	int getCount();
private:
	sf::Clock m_timer;
};