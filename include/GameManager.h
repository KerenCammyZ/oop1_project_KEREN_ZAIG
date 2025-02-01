#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <vector>
#include "GameObject.h"
#include "Player.h"
#include <unordered_map>
#include "GlobalSizes.h"
#include "Guard.h"
#include "Bomb.h"
#include "Door.h"

class GameManager {
public:
	GameManager();
	~GameManager();
	const sf::Texture& loadTexture(const std::string& texturePath);
	void runGame();
	void drawBoard();
	void drawLevel(int currLevel);
	void mainMenuScreen();
	void toolbar();
	void drawToolbar();
	void drawBombs(std::vector<Bomb*> &m_bombs);
	void explodeBomb(float x, float y);
private:
	std::vector<std::vector<GameObject*>> m_board;
	sf::RenderWindow m_window;
	int m_width = 0, m_height = 0, m_currLevel = 0;
	const int m_numOfLevels = 3;
	std::unordered_map<std::string, sf::Texture> m_textures;
	Player m_player;
	std::vector<Guard*> m_guards;
	sf::Text m_livesText, m_scoreText, m_levelText, m_helpText, m_exitText, m_timeText;
	sf::Font m_font;
	sf::Clock m_clock;
	std::vector<Bomb*> m_bombs;
	Door* m_currLeveldoor = nullptr;
	bool m_inGame = false;
};