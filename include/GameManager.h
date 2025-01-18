#include "Board.h"
#include "Player.h"

class GameManager {
public:
	void runGame();
	//bool openPlaylist();
	//void drawLevel(sf::RenderWindow& window, const std::string& fileName) const;

private:
	Board m_board;
	int m_toolbarHeight = 200; //space for toolbar
	int m_tileSize = 69; //size of each tile
	sf::RenderWindow m_window = sf::RenderWindow(sf::VideoMode(2400, 1600), "Bomberman");
	Player m_player;

	std::vector<std::string> m_levels;
	std::string m_currentLevelName;
};