#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class GameManager {
public:
	void runGame();
	bool openPlaylist();
	void drawLevel(sf::RenderWindow& window, const std::string& fileName, int levelIndex);
	bool openLevel(int i);

private:
	std::vector<std::string> m_levels;
	int m_currentLevelIndex = 0;
	std::string m_currentLevelName;
	bool m_levelCompleted = false;
	std::vector<std::vector<sf::RectangleShape>> m_board;
	int m_toolbarHeight = 50; //space for toolbar
	int m_tileSize = 50; //size of each tile
};