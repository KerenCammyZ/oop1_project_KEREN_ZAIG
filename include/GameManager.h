#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class GameManager {
public:
	void runGame();
	//bool openPlaylist();
	void drawLevel(sf::RenderWindow& window, const std::string& fileName) const;
	bool openLevel(int i);

private:
	std::vector<std::string> m_levels;
	int m_currentLevelIndex = 0;
	std::string m_currentLevelName;
	bool m_levelCompleted = false;
	std::vector<std::vector<sf::RectangleShape>> m_board;
	int m_toolbarHeight = 200; //space for toolbar
	int m_tileSize = 69; //size of each tile
	sf::RenderWindow m_window = sf::RenderWindow(sf::VideoMode(2400, 1600), "Bomberman");
};