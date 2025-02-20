#pragma once
#include "StaticObject.h"

class Rock : public StaticObject
{
public:
	Rock(int x, int y, sf::RenderWindow& window);
};