#include "GameObject.h"
#include <iostream>

GameObject::GameObject(sf::RenderWindow& window, sf::Vector2f position) : m_window(&window), m_position(position)
{
	m_sprite.setPosition(m_position);
}


void GameObject::draw() const
{	
	m_window->draw(m_sprite);
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

void GameObject::setPosition(const sf::Vector2f& position) 
{
	m_position = position;
	m_sprite.setPosition(position);
}

void GameObject::setTexture(sf::Texture texturePath)
{	
	m_texture = texturePath;
	m_sprite.setTexture(m_texture); 
}

void GameObject::setSprite(const sf::Sprite& sprite)
{
	m_sprite = sprite;
}

std::string GameObject::getName() const
{
	return m_name;
}

void GameObject::moveSprite(const sf::Vector2f& offset)
{
	m_sprite.move(offset);
}