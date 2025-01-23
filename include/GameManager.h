#include "GameObject.h"
#include <fstream>
#include <string>
#include <iostream>

class GameManager {
public:
	void runGame();
	void draw();
	//bool openPlaylist();
	void drawLevel(const std::string& fileName) const;

private:
	std::vector<std::vector<GameObject>> m_gameObjects;
	sf::RenderWindow m_window;
	int m_tileSize = 69;
	int m_width = 0, m_height = 0, m_lives = 3;
	
};