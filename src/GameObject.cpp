#include "GameObject.h"

GameObject::GameObject(sf::RenderWindow& window) : m_window(window), m_position(0, 0), m_tileSize(50){}

void GameObject::draw() const
{	
	m_window.draw(m_sprite);
}

sf::Vector2f GameObject::getPosition() const
{
	return m_position;
}

sf::Sprite GameObject::getSprite() const
{
	return m_sprite;
}

sf::Texture GameObject::getTexture() const
{
	return m_texture;
}

size_t GameObject::getTileSize() const
{
	return m_tileSize;
}

void GameObject::setPosition(const sf::Vector2f& position) 
{
	m_position = position;
}

void GameObject::setTexture(const std::string& texturePath)
{
	if (m_texture.loadFromFile(texturePath))
	{
		m_sprite.setTexture(m_texture);
	}
	else
	{
		std::cerr << "Error loading texture: " << texturePath << "\n";
	}
}

void GameObject::setTileSize(size_t tileSize)
{
	m_tileSize = tileSize;
}

void GameObject::setSprite(const sf::Sprite& sprite)
{
	m_sprite = sprite;
}

void GameObject::setSpriteTexture(sf::Texture)
{
	m_sprite.setTexture(m_texture);
}





