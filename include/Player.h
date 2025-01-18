#pragma once
#include "Board.h"

class Player {
public:
	Player();
	void drawPlayer(sf::RenderWindow& window);
	void movePlayer(int x, int y, Board &board);
private:
	sf::Texture m_playerTexture;
	sf::Sprite m_playerSprite;
	int m_toolbarHeight = 200; //space for toolbar
	int m_tileSize = 69; //size of each tile
	sf::Texture m_wallTexture, m_rockTexture, m_doorTexture;
	
};

