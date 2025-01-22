#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class Board {
public:
	Board();
	void drawLevel(sf::RenderWindow& window, const std::string& fileName);
	sf::Vector2f getTilePosition(int row, int col);
    sf::Texture* getTexture(sf::Vector2f position); //TODO: finish
private:
	int m_row;
	int m_col;
	std::vector<std::vector<sf::Sprite>> m_board;
	int m_toolbarHeight = 200; //space for toolbar TODO: add to parent class
	int m_tileSize = 69; //size of each tile TODO: add to parent class
};