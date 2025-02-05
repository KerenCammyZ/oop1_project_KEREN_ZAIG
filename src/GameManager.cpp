#include "GameManager.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "Guard.h"
#include "Wall.h"
#include "Rock.h"
#include "Door.h"
#include "Bomb.h"
#include <random>

GameManager::GameManager() : m_player(m_window, sf::Vector2f(m_tileSize, m_tileSize)) {
	m_width = 0;
	m_height = 0;

	if (!m_font.loadFromFile("Orange Kid.otf")) {
		std::cerr << "Error: Cannot load font 'Orange Kid.otf'\n";
	}

	m_player.setTexture(ResourceManager::instance().getTexture(Texture::player));
	m_player.setPosition(sf::Vector2f(m_tileSize, m_tileSize));
}

GameManager::~GameManager() {
	for (auto& row : m_board) {
		for (auto& obj : row) {
			delete obj;
			obj = nullptr; // Avoid dangling pointers
		}
	}
	m_board.clear();
}


void GameManager::drawBoard()
{
	if (m_window.isOpen() && !m_board.empty()) {
		for (const auto& row : m_board) {
			for (const auto& obj : row) {
				if (obj != nullptr) { 
					obj->draw();
				}
			}
		}
	}
}

void GameManager::drawLevel(int level)
{
	std::string fileName = "level" + std::to_string(level) + ".txt";
	std::ifstream file(fileName);
	if (!file) {
		std::cerr << "Cannot open level file: " << fileName << "\n";
		return;
	}

	// Read the file into lines to determine the size
	std::vector<std::string> lines;
	std::string line;
	while (std::getline(file, line))
	{
		lines.push_back(line);
	}

	// Initialize level dimensions
	int numRows = lines.size();
	int numCols = lines.empty() ? 0 : lines[0].size();

	// Set window size based on level
	int windowWidth = numCols * m_tileSize;
	int windowHeight = (numRows * m_tileSize);
	m_window.create(sf::VideoMode(windowWidth, windowHeight + m_tileSize), "Bomberman");
	m_width = windowWidth;
	m_height = windowHeight + m_tileSize;

	m_board.resize(numRows);
	for (auto& row : m_board) {
		row.resize(numCols, nullptr);
	}

	//reset guards if its a new level
	m_guards.clear();

	//reset time if its a new level
	m_timeLevel = false;

	std::vector<std::pair<int, int>> emptyTiles; // Store empty tile positions

	for (int row = 0; row < numRows; ++row) {
		for (int col = 0; col < numCols; ++col) {
			char tile = lines[row][col];
			GameObject* gameObject = nullptr;
			Guard* g = nullptr;

			switch (tile) {
			case '#':
				gameObject = new Wall(col * m_tileSize, m_tileSize + row * m_tileSize, m_window);
				gameObject->setTexture(ResourceManager::instance().getTexture(Texture::wall));
				break;
			case '@':
				gameObject = new Rock(col * m_tileSize, m_tileSize + row * m_tileSize, m_window);
				gameObject->setTexture(ResourceManager::instance().getTexture(Texture::rock));
				break;
			case 'D':
				gameObject = new Door(col * m_tileSize, m_tileSize + row * m_tileSize, m_window);
				gameObject->setTexture(ResourceManager::instance().getTexture(Texture::door));
				m_currLeveldoor = dynamic_cast<Door*>(gameObject);
				break;
			case '!':
				m_guards.push_back(std::make_unique<Guard>(m_window, sf::Vector2f(col * m_tileSize, m_tileSize + row * m_tileSize)));
				m_guards.back()->setTexture(ResourceManager::instance().getTexture(Texture::guard));
				m_guards.back()->setType(GUARD);
				break;
			default:
				// Track empty spots
				emptyTiles.push_back({ row, col });
				break;
			}

			m_board[row][col] = gameObject;
			if (gameObject && !gameObject->getSprite().getTexture()) {
				std::cerr << "Error: object texture not set properly.\n";
			}
		}
	}

	if (!m_guards.empty())
		m_levelNumGuards = m_guards.size();

	
	// ADD 4 RANDOM POWERUPS
	m_powers.clear(); // Clear any existing power-ups

	if (emptyTiles.size() >= 4) {
		// Shuffle empty tile positions
		std::random_device rd;
		std::mt19937 g(rd());
		std::shuffle(emptyTiles.begin(), emptyTiles.end(), g);

		// Select the first 4 empty positions for PowerUps
		for (int i = 0; i < 4; i++) {
			int row = emptyTiles[i].first;
			int col = emptyTiles[i].second;
			float x = col * m_tileSize;
			float y = m_tileSize + row * m_tileSize;

			int randomNum = std::rand() % 4; //random num 0 to 3
			PowerUp* powerUp = nullptr;

			switch (randomNum)
			{
			case 0:
				powerUp = new PowerUp(x, y, DISSAPEAR, m_window);
				powerUp->setTexture(ResourceManager::instance().getTexture(Texture::dissapear));
				break;
			case 1:
				powerUp = new PowerUp(x, y, TIME, m_window);
				powerUp->setTexture(ResourceManager::instance().getTexture(Texture::time));
				m_timeLevel = true; //make it a time level if this powerup appears
				break;
			case 2:
				powerUp = new PowerUp(x, y, FREEZE, m_window);
				powerUp->setTexture(ResourceManager::instance().getTexture(Texture::freeze));
				break;
			case 3:
				powerUp = new PowerUp(x, y, LIFE, m_window);
				powerUp->setTexture(ResourceManager::instance().getTexture(Texture::life));
				break;
			default:
				break;
			}

			m_powers.push_back(powerUp);
		}
	}

	if (m_timeLevel)
	{
		m_clock.restart();
	}
}

void GameManager::mainMenuScreen()
{
	int menuSize = 1000;
	m_window.create(sf::VideoMode(menuSize, menuSize), "Bomberman Main Menu");
	if (!m_mainMenuMusic.openFromFile("mainMenuMusic.ogg"))
	{
		std::cerr << "Can't load main menu music\n";
	}
	m_mainMenuMusic.setLoopPoints({sf::milliseconds(500), sf::seconds(114)});
	m_mainMenuMusic.setLoop(true);
	m_mainMenuMusic.setVolume(10.f);
	m_mainMenuMusic.play();

	//sf::Sprite backround
	

	sf::Font font;
	if (!font.loadFromFile("Orange Kid.otf"))
	{ 
		std::cerr << "Cannot load font\n";
	}

	sf::Text play, help;
	play.setFont(font);
	help.setFont(font);
	play.setFillColor(sf::Color::Black);
	help.setFillColor(sf:: Color::Black);
	play.setString("PLAY");
	help.setString("HELP");
	play.setCharacterSize(150);
	help.setCharacterSize(100);
	int centerX = (menuSize / 2) - play.getGlobalBounds().width / 2;
	int centerY = (menuSize / 2) - play.getGlobalBounds().height;
	play.setPosition(sf::Vector2f(centerX,centerY - 20));
	help.setPosition(sf::Vector2f(centerX + 50, centerY + 200));

	
	while (m_window.isOpen())
	{
		sf::Event event;
		while (m_window.pollEvent(event)) 
		{
			switch (event.type) 
			{
			case sf::Event::Closed:
				m_window.close();
				break;
			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
					if (play.getGlobalBounds().contains(mousePos))
					{
						m_inGame = true;
						m_mainMenuMusic.stop();
						runGame();
					}
					if (help.getGlobalBounds().contains(mousePos))
					{
						helpScreen();
					}
				}
				break;
			default:
				break;
			}
		}

		m_window.clear(sf::Color::White);
		m_window.draw(play);
		m_window.draw(help);
		m_window.display();
	}
}

void GameManager::toolbar()
{
	m_livesText.setFont(m_font);
	m_scoreText.setFont(m_font);
	m_levelText.setFont(m_font);
	m_exitText.setFont(m_font);
	m_timeText.setFont(m_font);

	m_livesText.setFillColor(sf::Color::Black);
	m_scoreText.setFillColor(sf::Color::Black);
	m_levelText.setFillColor(sf::Color::Black);
	m_exitText.setFillColor(sf::Color::Black);
	m_timeText.setFillColor(sf::Color::Black);

	m_livesText.setCharacterSize(70);
	m_scoreText.setCharacterSize(70);
	m_levelText.setCharacterSize(70);
	m_exitText.setCharacterSize(70);
	m_timeText.setCharacterSize(70);

	int toolbarY = 2;
	int toolbarX = 0;
	m_levelText.setPosition(sf::Vector2f(toolbarX, toolbarY));
	m_livesText.setPosition(sf::Vector2f(toolbarX + (5 *m_tileSize), toolbarY));
	m_scoreText.setPosition(sf::Vector2f(toolbarX + (10 * m_tileSize), toolbarY));
	m_timeText.setPosition(sf::Vector2f(toolbarX + (15 * m_tileSize), toolbarY));
	m_exitText.setPosition(sf::Vector2f(toolbarX + (20 * m_tileSize), toolbarY));

}

void GameManager::drawToolbar()
{
	if (m_livesText.getFont() == nullptr) {
		return;
	}
	if (!m_window.isOpen()) {
		return;
	}
	m_livesText.setString("Lives: " + std::to_string(m_player.getLives()));
	m_scoreText.setString("Score: " + std::to_string(m_score));
	m_levelText.setString("Level: " + std::to_string(m_currLevel));
	m_exitText.setString("Exit");

	int minutes = 0;
	int seconds = 0;

	if (m_timeLevel)
	{
		minutes = (3 * 60 - m_clock.getElapsedTime().asSeconds() + 1) / 60;
		seconds = (3 * 60 - int(m_clock.getElapsedTime().asSeconds())) % 60;
	}
	else
	{
		minutes = m_clock.getElapsedTime().asSeconds() / 60;
		seconds = int(m_clock.getElapsedTime().asSeconds()) % 60;
	}
	if(seconds < 10)
		m_timeText.setString("Time: " + std::to_string(minutes) + ":0" + std::to_string(seconds));
	else
		m_timeText.setString("Time: " + std::to_string(minutes) + ":" + std::to_string(seconds));

	m_window.draw(m_livesText);
	m_window.draw(m_scoreText);
	m_window.draw(m_levelText);
	m_window.draw(m_exitText);
	m_window.draw(m_timeText);
}

void GameManager::drawBombs()
{
	if (m_bombs.empty())
		return;
	else
	{
		for (int i = 0; i < m_bombs.size(); i++)
		{
			int currTime = m_bombs[i]->getCount();
			switch (currTime)
			{
			case 0:
			case 1:
				m_bombs[i]->setTexture(ResourceManager::instance().getTexture(Texture::bomb1));
				break;
			case 2:
				m_bombs[i]->setTexture(ResourceManager::instance().getTexture(Texture::bomb2));
				break;
			case 3:
				m_bombs[i]->setTexture(ResourceManager::instance().getTexture(Texture::bomb3));
				break;
			case 4:
				m_bombs[i]->setTexture(ResourceManager::instance().getTexture(Texture::bomb4));
				break;
			case 5:
				m_bombs[i]->setTexture(ResourceManager::instance().getTexture(Texture::explosion));
				
				break;
			default:
				sf::Vector2f bombPos = m_bombs[i]->getPosition();
				float x = bombPos.x / m_tileSize;
				float y = bombPos.y / m_tileSize;

				explodeBomb(x, y);
				if (m_bombs[i]->getBounds().intersects(m_player.getBounds()))
				{
					m_player.lostLife();
				}
				m_bombs.erase(m_bombs.begin() + i);
				--i; // Adjust index after erasing
				continue;
			}
			if (m_bombs[i] != nullptr) // Check again before drawing
				m_bombs[i]->draw();
		
		}
	}
}

void GameManager::explodeBomb(float x, float y)
{
	m_explosionSound.setBuffer(ResourceManager::instance().getSound(Sound::explosion));
	m_explosionSound.setVolume(10.f);
	m_explosionSound.play();
	std::vector<std::pair<int, int>> explosionArea = {
		{x, y}, {x + 1, y}, {x - 1, y}, {x, y + 1}, {x, y - 1},
		{x + 1, y + 1}, {x - 1, y + 1}, {x - 1, y - 1}, {x + 1, y - 1}
	};

	int maxRows = m_board.size();
	int maxCols = (maxRows > 0) ? m_board[0].size() : 0;


	for (auto& [ex, ey] : explosionArea)
	{
		// Ensure indices are within bounds
		if (ex < 0 || ey < 0 || ey >= maxRows || ex >= maxCols)
			continue;

		GameObject* obj = m_board[ey][ex];

		if (!obj) continue;

		switch (obj->getType())
		{
		case ROCK:
			delete obj;
			m_board[ey][ex] = nullptr;
			break;

		default:
			break;
		}
	}
	for (size_t i = 0; i < m_guards.size(); i++)
	{
		if (!m_guards[i]) continue;

		sf::FloatRect guardBounds = m_guards[i]->getBounds();

		// Check if guard is within explosion radius
		for (auto& [ex, ey] : explosionArea)
		{
			sf::Vector2f explosionPos(ex * m_tileSize, ey * m_tileSize);
			if (guardBounds.contains(explosionPos))
			{
				killGuard(i);
				--i; // Adjust index after erasing
				break; // Exit inner loop once guard is removed
			}
		}
	}
}

void GameManager::drawGuards()
{
	if (!m_guards.empty())
	{
		for (int i = 0; i < m_guards.size(); i++)
		{
			m_guards[i]->draw();
		}
	}
}

void GameManager::killGuard(int i)
{
	if (m_guards.size() > i)
	{
		m_guards.erase(m_guards.begin() + i);
	}
	m_score += 5;
}

void GameManager::activatePowerUps()
{
	if (!m_powers.empty())
	{
		for (int i = 0; i < m_powers.size(); i++)
		{

			ObjectType type = m_powers[i]->getType();
			int addTime;
			if (m_player.getBounds().intersects(m_powers[i]->getBounds()))
			{
				switch (type)
				{
				case DISSAPEAR:

					if (!m_guards.empty())
					{
						int randNum = std::rand() % m_guards.size();
						killGuard(randNum);
					}
					deletePowerUp(i);

					break;
				case TIME:

					// Add 3 minutes (180 seconds) to the countdown timer
					m_extraTime = 180 + m_clock.getElapsedTime().asSeconds();
					m_clock.restart();
					deletePowerUp(i);

					break;
				case FREEZE:

					m_powers[i]->activate();
					setGuardsFrozen(true);
					m_freezeStartTime = m_clock.getElapsedTime().asSeconds(); // Store freeze activation time
					m_guardsFrozen = true;  // Mark that the freeze effect is active
					deletePowerUp(i);

					break;

					break;
				case LIFE:

					m_player.setLives(m_player.getLives() + 1);
					deletePowerUp(i);

					break;

				}
				m_powerupSound.setBuffer(ResourceManager::instance().getSound(Sound::powerup));
				m_powerupSound.play();
			}
			
		}
	}
	// Unfreeze guards after 5 seconds
	if (m_guardsFrozen && m_clock.getElapsedTime().asSeconds() >= m_freezeStartTime + 5)
	{
		setGuardsFrozen(false);
		m_guardsFrozen = false;  // Reset frozen state
	}
}

void GameManager::setGuardsFrozen(bool freeze)
{
	if (!m_guards.empty())
	{
		for (int i = 0; i < m_guards.size(); i++)
		{
			m_guards[i]->setFrozen(freeze);
		}
	}
}

void GameManager::deletePowerUp(int i)
{
	if (!m_powers.empty())
	{
		delete m_powers[i];
		m_powers[i] = nullptr;
		m_powers.erase(m_powers.begin() + i);
	}
}

void GameManager::drawPowerUps(const std::vector<PowerUp*>& m_powers)
{
	for (int i = 0; i < m_powers.size(); i++)
	{
		m_powers[i]->draw();
	}
}

void GameManager::endScreen(bool flag)
{

	int menuSize = 1000;
	m_window.create(sf::VideoMode(menuSize, menuSize), "Bomberman");
	sf::Font font;
	if (!font.loadFromFile("Orange Kid.otf"))
	{
		std::cerr << "Cannot load font\n";
	}

	sf::Text text, playAgain;
	text.setFont(font);
	playAgain.setFont(font);
	text.setFillColor(sf::Color::Black);
	playAgain.setFillColor(sf::Color::Black);
	if (flag)
		text.setString("YOU WON!");
	else
	{
		text.setString("YOU LOSE");
	}
	playAgain.setString("Play Again");
	text.setCharacterSize(150);
	playAgain.setCharacterSize(100);
	int centerX = (menuSize / 2) - text.getGlobalBounds().width / 2;
	int centerY = (menuSize / 2) - text.getGlobalBounds().height;
	text.setPosition(sf::Vector2f(centerX, centerY - 20));
	playAgain.setPosition(sf::Vector2f(centerX + 60, centerY + 210));

	sf::Sprite backround;
	backround.setTexture(ResourceManager::instance().getTexture(Texture::EndScreen));

	while (m_window.isOpen())
	{
		sf::Event event;
		while (m_window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				m_window.close();
				exit(EXIT_SUCCESS);
				break;
			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
					if (playAgain.getGlobalBounds().contains(mousePos))
					{
						startNewGame();
//						mainMenuScreen();
					}
				}
				break;
			default:
				break;
			}
		}

		m_window.clear(sf::Color::White);
		m_window.draw(backround);
		m_window.draw(text);
		m_window.draw(playAgain);
		m_window.display();
	}
}

void GameManager::helpScreen()
{
	int menuSize = 1000;
	m_window.create(sf::VideoMode(menuSize, menuSize), "How to Play");
	sf::Font font;
	if (!font.loadFromFile("Orange Kid.otf"))
	{
		std::cerr << "Cannot load font\n";
	}

	sf::Text PLAY;
	PLAY.setFont(font);
	PLAY.setCharacterSize(100);
	
	int centerTitleX = (menuSize / 2) - (PLAY.getGlobalBounds().width / 2) - 80;

	PLAY.setPosition(centerTitleX, menuSize - 150);
	PLAY.setString("PLAY");
	PLAY.setFillColor(sf::Color::Black);

	sf::Texture backroundTexture;
	if (!backroundTexture.loadFromFile("HELP SCREEN.png"))
	{
		std::cerr << "Cannot load HELP SCREEN\n";
	}
	sf::Sprite backround;
	backround.setTexture(backroundTexture);
	
	while (m_window.isOpen())
	{
		sf::Event event;
		while (m_window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				m_window.close();
				exit(EXIT_SUCCESS);
				break;
			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
					if (PLAY.getGlobalBounds().contains(mousePos))
					{
						m_inGame = true;
						m_mainMenuMusic.stop();
						runGame();
					}
				}
				break;
			default:
				break;
			}
		}

		m_window.clear(sf::Color::White);
		m_window.draw(backround);
		m_window.draw(PLAY);
		m_window.display();
	}

}

void GameManager::runGame() 
{

	if (m_inGame == false)
	{
		mainMenuScreen();
	}
	else
	{
		m_currLevel = 1;
		sf::Music music;
		if (!music.openFromFile("inGameMusic.ogg"))
		{
			std::cerr << "Can't load in game music\n";
		}
		music.setLoopPoints({ sf::milliseconds(500), sf::seconds(84) });
		music.setLoop(true);
		music.setVolume(5.f);
		music.play();


		while (m_currLevel != 4)
		{

			// Load level
			drawLevel(m_currLevel);
			m_window.setFramerateLimit(60);
			m_player.respawn();
			
			m_gameBackround.setTexture(ResourceManager::instance().getTexture(Texture::gameBackround));

			//add toolbar
			toolbar();

			sf::Clock clock;
			m_clock.restart();
			m_extraTime = 0;

			// Main game loop
			while (m_window.isOpen())
			{

				// Calculate delta time for this frame
				const auto deltaTime = clock.restart();
				int currLives = m_player.getLives();
				// Process events
				sf::Event event;
				while (m_window.pollEvent(event)) {
					switch (event.type) {
					case sf::Event::Closed:
						m_window.close();
						return; // exit game
						break;

					case sf::Event::KeyPressed:
						if (event.key.code == sf::Keyboard::B)
						{
							m_bombs.push_back(std::make_unique<Bomb>(m_window, m_player.getSprite().getPosition().x, m_player.getSprite().getPosition().y));
						}
						else
							m_player.setDirection(event.key.code);

						break;

					default:
						break;
					}
				}

				// Update game state

				//check for game overs
				int elapsedTime = m_clock.getElapsedTime().asSeconds();
				if (m_timeLevel)
				{
					// TIMED LEVEL: Count down from 3 minutes + extra time
					int timeLeft = (3 * 60 + m_extraTime) - elapsedTime;
					if (timeLeft <= 0)
					{
						music.stop();
						endScreen(false);
					}
				}
				
				if (m_player.getLives() == 0)
				{
					music.stop();
					endScreen(false);
				}

				//no game over, do normal events
				m_player.move(deltaTime, m_board, m_player);
				activatePowerUps();
				for (auto& guard : m_guards) {
					guard->move(deltaTime, m_board, m_player);
				}
				if (m_player.getLives() < currLives)
				{
					m_gameOverSound.setBuffer(ResourceManager::instance().getSound(Sound::dead));
					m_gameOverSound.setVolume(10.f);
					m_gameOverSound.play();
				}
				if (m_currLeveldoor->getPassed())
				{
					m_score = 25 + (3 * m_levelNumGuards);
					m_currLevel++;
					m_levelUpSound.setBuffer(ResourceManager::instance().getSound(Sound::levelup));
					m_levelUpSound.play();
					m_window.close();
				}
				
				// Render the scene
				m_window.clear(sf::Color::White);
				m_window.draw(m_gameBackround);
				drawBoard();
				m_player.draw();
				if (!m_bombs.empty())
					drawBombs();
				if (!m_powers.empty())
					drawPowerUps(m_powers);
				drawGuards();
				drawToolbar();
				m_window.display();
			}
		}
		music.stop();
		endScreen(true);
	}
}

void GameManager::startNewGame() {

	// Close the existing window
	/*if (m_window.isOpen()) {
		m_window.close();
	}*/

	m_window.close();

	// Reset player stats
	m_player.setLives(3);  // Set default lives
	m_score = 0;           // Reset score
	m_currLevel = 1;       // Start at level 1
	m_timeLevel = false;

	// Clear existing game objects
	for (auto& row : m_board) {
		for (auto& obj : row) {
			delete obj;
			obj = nullptr;
		}
	}
	m_board.clear();

	// Clear guards
	m_guards.clear();

	// Clear power-ups
	for (auto& powerUp : m_powers) {
		delete powerUp;
	}
	m_powers.clear();

	// Reset clock
	m_clock.restart();

	m_inGame = false;
	//m_currLeveldoor->setPassed(false);
}