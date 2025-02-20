#include "PowerUp.h"

PowerUp::PowerUp(int x, int y, ObjectType type, sf::RenderWindow& window) : StaticObject(x, y, type, window) 
{
	m_active = false;
}

void PowerUp::draw() const
{
	if (!m_active)
	{
		m_window->draw(m_sprite);
	}
}

void PowerUp::activate()
{
    if (!m_active) {
        m_active = true;
    }
}

void PowerUp::reset()
{
    m_active = false;
}
