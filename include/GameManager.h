#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <fstream>
#include <iostream>
#include <vector>
#include <memory>
#include "GameObject.h"
#include "Player.h"
#include <unordered_map>
#include "GlobalSizes.h"
#include "Guard.h"
#include "Bomb.h"
#include "Door.h"
#include "PowerUp.h"

class GameManager {
public:
	enum class GameState { MAIN_MENU, IN_GAME, HELP_SCREEN, END_SCREEN };
	void run();
	GameManager();
	~GameManager();
	GameState runGame();
	void startNewGame();
	void drawBoard();
	void drawLevel(int currLevel);
	GameState mainMenuScreen();
	void toolbar();
	void drawToolbar();
	void drawBombs();
	void explodeBomb(float x, float y);
	void drawGuards();
	void killGuard(int i);
	void activatePowerUps();
	void setGuardsFrozen(bool freeze);
	void deletePowerUp(int i);
	void drawPowerUps(const std::vector<PowerUp*>& m_powers);
	GameState endScreen(bool flag);
	GameState helpScreen();
private:
	//std::vector<std::vector<GameObject*>> m_board;
	std::vector<std::vector<std::unique_ptr<GameObject>>> m_board;
	sf::RenderWindow m_window;
	int m_width = 0, m_height = 0, m_currLevel = 0, m_score = 0, m_levelNumGuards = 0, m_freezeStartTime = -1;
	const int m_numOfLevels = 3;
	Player m_player;
	std::vector<std::unique_ptr<Guard>> m_guards;
	std::vector<PowerUp*> m_powers; 
	sf::Text m_livesText, m_scoreText, m_levelText, m_exitText, m_timeText;
	sf::Font m_font;
	sf::Clock m_clock;
	std::vector<std::unique_ptr<Bomb>> m_bombs;
	//Door* m_currLeveldoor = nullptr;
	GameObject* m_currLeveldoor; // Keep a raw pointer to the door
	bool m_inGame = false, m_guardsFrozen = false, m_timeLevel = false, m_won = false;
	int m_extraTime = 0;
	sf::Sound m_powerupSound, m_explosionSound, m_levelUpSound, m_gameOverSound;
	sf::Music m_mainMenuMusic;
	sf::Sprite m_gameBackround;
};