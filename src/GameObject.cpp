#include "GameObject.h"
#include <iostream>

GameObject::GameObject(sf::RenderWindow& window, sf::Vector2f position) : m_window(window), m_position(position), m_tileSize(20)
{
	m_sprite.setPosition(m_position);
}


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
	m_sprite.setPosition(position);
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





