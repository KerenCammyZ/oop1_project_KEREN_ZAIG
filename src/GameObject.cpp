#include "GameObject.h"
#include <iostream>

GameObject::GameObject(int x, int y, ObjectType objType, sf::RenderWindow& window) : m_x(x), m_y(y), m_type(objType), m_window(&window)
{
	m_position = sf::Vector2f(x, y);
	m_sprite.setPosition(m_position);
}

void GameObject::draw() const
{	
	if (m_window)
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
	m_sprite.setPosition(m_position);
}

void GameObject::setSprite(const sf::Sprite& sprite)
{
	m_sprite = sprite;
}

sf::FloatRect GameObject::getBounds() const
{
	return m_sprite.getGlobalBounds();
}

ObjectType GameObject::getType() const
{
	return m_type;
}

void GameObject::setType(ObjectType obj)
{
	m_type = obj;
}


bool GameObject::checkCollision(GameObject* a, GameObject* b)
{
	return (a->getX() < b->getX() + b->getWidth() &&
		a->getX() + a->getWidth() > b->getX() &&
		a->getY() < b->getY() + b->getHeight() &&
		a->getY() + a->getHeight() > b->getY());
}

int GameObject::getX()
{
	return m_position.x / m_tileSize;
}

int GameObject::getY()
{
	return m_position.y / m_tileSize;
}

int GameObject::getWidth()
{
	return m_sprite.getGlobalBounds().width;
}

int GameObject::getHeight()
{
	return m_sprite.getGlobalBounds().height;
}