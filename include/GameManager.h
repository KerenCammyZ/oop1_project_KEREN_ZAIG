#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <vector>
#include "GameObject.h"

class GameManager {
public:
	GameManager();
	~GameManager();
	void runGame();
	void draw();
	//bool openPlaylist();
	void drawLevel(const std::string& fileName);

private:
	std::vector<std::vector<GameObject*>> m_gameObjects;
	sf::RenderWindow m_window;
	int m_tileSize = 69;
	int m_width, m_height, m_lives = 3;
	
};