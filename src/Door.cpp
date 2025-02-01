#include "Door.h"

Door::Door(int x, int y, sf::RenderWindow& window) : StaticObject(x, y, DOOR, window) 
{
	m_passed = false;
}

bool Door::getPassed() const
{
	return m_passed;
}

void Door::setPassed(bool passed)
{
	m_passed = passed;
}
