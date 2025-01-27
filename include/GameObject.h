#pragma once
#include <SFML/Graphics.hpp>
class GameObject {
public:
	GameObject() = default;
	GameObject(sf::RenderWindow &window, sf::Vector2f position);
	void draw() const;
	sf::Vector2f getPosition() const;
	sf::Sprite getSprite() const;
	sf::Texture getTexture() const;
	int getTileSize() const;
	void setPosition(const sf::Vector2f& position);
	void setTexture(sf::Texture texturePath);
	void setTileSize(int tileSize);
	void setSprite(const sf::Sprite& sprite);
	void setSpriteTexture(sf::Texture);
	std::string getName() const;
private:
	sf::RenderWindow* m_window; // Change to pointer
	sf::Vector2f m_position = sf::Vector2f(0,0);
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	std::string m_name;
	int m_tileSize;
};