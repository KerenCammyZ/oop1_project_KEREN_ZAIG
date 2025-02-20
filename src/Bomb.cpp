#include "Bomb.h"
#include "Player.h"


Bomb::Bomb(sf::RenderWindow& window, float x, float y)
    : StaticObject(x, y, BOMB, window) {
}

int Bomb::getCount()
{
	return m_timer.getElapsedTime().asSeconds();
}
