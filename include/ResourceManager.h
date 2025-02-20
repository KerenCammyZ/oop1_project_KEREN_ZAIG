#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <vector>

enum class Texture
{
	bomb1,
	bomb2,
	bomb3,
	bomb4,
	explosion,
	EndScreen,
	gameBackround,
	player,
	wall,
	rock,
	door,
	guard,
	dissapear,
	time,
	freeze,
	life,
};

enum class Sound
{
	explosion,
	powerup,
	dead,
	levelup,
};

class ResourceManager
{
public:
	static ResourceManager& instance();

	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;

	const sf::Texture& getTexture(Texture texture) const;
	const sf::SoundBuffer& getSound(Sound sound) const;

private:
	ResourceManager();
	std::vector<sf::Texture> m_textures;
	std::vector<sf::SoundBuffer> m_sounds;
};