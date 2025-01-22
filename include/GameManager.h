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
	size_t toolbarSize = 69;
	size_t m_width, m_height, m_tileSize;
};