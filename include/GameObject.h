#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "GameManager.h"

class GameObject : public GameManager{
public:
	GameObject() = default;
	GameObject(sf::RenderWindow &window);
	void draw() const;
	sf::Vector2f getPosition() const;
	sf::Sprite getSprite() const;
	sf::Texture getTexture() const;
	size_t getTileSize() const;
	void setPosition(const sf::Vector2f& position);
	void setTexture(const std::string& texturePath);
	void setTileSize(size_t tileSize);
	void setSprite(const sf::Sprite& sprite);
	void setSpriteTexture(sf::Texture);
private:
	sf::RenderWindow &m_window;
	sf::Vector2f m_position = sf::Vector2f(0,0);
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	size_t m_tileSize;
};