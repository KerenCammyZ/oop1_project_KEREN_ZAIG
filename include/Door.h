#pragma once
#include "StaticObject.h"

class Door : public StaticObject
{
public:
    Door(int x, int y, sf::RenderWindow& window);
    bool getPassed() const;
    void setPassed(bool passed);
private:
    bool m_passed = false;
};