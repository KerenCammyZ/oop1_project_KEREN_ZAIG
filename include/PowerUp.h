#pragma once
#include "StaticObject.h"

class PowerUp : public StaticObject
{
public:
	PowerUp(int x, int y, ObjectType type, sf::RenderWindow& window);
	void draw() const override;
	void activate();
	void reset();
	bool getActive() const{ return m_active; }
private:
	bool m_active = false;
};