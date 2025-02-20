#pragma once
#include "StaticObject.h"

class Wall : public StaticObject
{
public:
	Wall(int x, int y, sf::RenderWindow& window);
};