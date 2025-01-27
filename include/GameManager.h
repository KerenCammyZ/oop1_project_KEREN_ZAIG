#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <vector>
#include "GameObject.h"
#include "Player.h"
#include <unordered_map>

class GameManager {
public:
	GameManager();
	~GameManager();
	const sf::Texture& getTexture(const std::string& texturePath);
	void runGame();
	void draw();
	//bool openPlaylist();
	void drawLevel(const std::string& fileName);

private:
	std::vector<std::vector<GameObject*>> m_gameObjects;
	sf::RenderWindow m_window;
	int m_tileSize;
	int m_width, m_height;
	std::unordered_map<std::string, sf::Texture> m_textures;
	Player m_player;
};