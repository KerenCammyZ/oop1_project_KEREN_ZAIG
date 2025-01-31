#pragma once
#include <SFML/Graphics.hpp>
#include "GlobalSizes.h"

class GameObject {
public:
	virtual ~GameObject() = default; // Add virtual destructor
	GameObject() = default;
	GameObject(int x, int y, ObjectType type, sf::RenderWindow& window);
	virtual void draw() const;
	sf::Vector2f getPosition() const;
	sf::Sprite getSprite() const;
	sf::Texture getTexture() const;
	void setPosition(const sf::Vector2f& position);
	void setTexture(sf::Texture texturePath);
	void setSprite(const sf::Sprite& sprite);
	sf::FloatRect getBounds() const;
	ObjectType getType() const;
	void setType(ObjectType obj);
	bool checkCollision(GameObject* a, GameObject* b);
	int getX();
	int getY();
	int getWidth();
	int getHeight();

protected:
	sf::RenderWindow* m_window; // Change to pointer
	sf::Vector2f m_position = sf::Vector2f(0,0);
	int m_x, m_y;
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	ObjectType m_type;

	friend class MovingObject;
	friend class StaticObject;
};