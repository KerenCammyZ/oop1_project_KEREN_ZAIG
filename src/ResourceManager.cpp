#include "ResourceManager.h"
#include <iostream>

ResourceManager& ResourceManager::instance()
{
	static auto instance = ResourceManager();
	return instance;
}

const sf::Texture& ResourceManager::getTexture(Texture texture) const
{
	return m_textures[static_cast<int>(texture)];
}

const sf::SoundBuffer& ResourceManager::getSound(Sound sound) const
{
	return m_sounds[static_cast<int>(sound)];
}

ResourceManager::ResourceManager()
{
	const std::vector<std::string> textureFiles =
	{
	"bomb1.png",
	"bomb2.png",
	"bomb3.png",
	"bomb4.png",
	"explosion.png",
	"EndScreen.png",
	"gameBackround.png",
	"player.png",
	"wall.png",
	"rock.png",
	"door.png",
	"guard.png",
	"dissapear.png",
	"time.png",
	"freeze.png",
	"life.png",
	};

	const std::vector<std::string> soundFiles =
	{
		"explosion.ogg",
		"powerup.ogg",
		"dead.ogg",
		"levelup.ogg",
	};

	for (const auto& name : textureFiles)
	{
		sf::Texture texture;
		if (!texture.loadFromFile(name)) {
			std::cerr << "Error loading texture: " << name << "\n";
		}
		m_textures.push_back(std::move(texture));
	}

	for (const auto& name : soundFiles)
	{
		sf::SoundBuffer sound;
		if (!sound.loadFromFile(name)) {
			std::cerr << "Error loading sound: " << name << "\n";
		}
		m_sounds.push_back(std::move(sound));
	}
}
