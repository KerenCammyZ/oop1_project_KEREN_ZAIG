#pragma once
#include <SFML/Graphics.hpp>
#include "GlobalSizes.h"

class GameObject {
protected:
	std::string m_type; //type of object
public:
	virtual ~GameObject() = default; // Add virtual destructor
	GameObject() = default;
	GameObject(sf::RenderWindow &window, sf::Vector2f position);
	void draw() const;
	sf::Vector2f getPosition() const;
	sf::Sprite getSprite() const;
	sf::Texture getTexture() const;
	void setPosition(const sf::Vector2f& position);
	void setTexture(sf::Texture texturePath);
	void setSprite(const sf::Sprite& sprite);
	std::string getName() const;
	sf::FloatRect getBounds() const;
	std::string getType() const;
	void setType(const std::string& type);

	bool checkCollision(GameObject* a, GameObject* b);

private:
	sf::RenderWindow* m_window; // Change to pointer
	sf::Vector2f m_position = sf::Vector2f(0,0);
	sf::Texture m_texture;
	std::string m_name;
	sf::Sprite m_sprite;

	friend class MovingObject;
	friend class Guard;
};