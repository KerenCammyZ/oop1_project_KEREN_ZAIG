#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
class GameObject : public GameManager{
public:
	void draw(sf::RenderWindow& window) const;
	//sf::Vector2f getPosition() const;
	//sf::Sprite getSprite() const;
	//sf::Texture getTexture() const;
	//size_t getTileSize() const;
	//void setPosition(const sf::Vector2f& position);
	//void setTexture(const std::string& texturePath);
	//void setTileSize(size_t tileSize);
private:
	sf::RenderWindow m_window;
	sf::Vector2f m_position;
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	size_t m_tileSize;
};