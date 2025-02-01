#include "GameManager.h"
#include "GameObject.h"
#include "Guard.h"
#include "Wall.h"
#include "Rock.h"
#include "Door.h"
#include "Bomb.h"

GameManager::GameManager() : m_player(m_window, sf::Vector2f(m_tileSize, m_tileSize)) {
	m_width = 0;
	m_height = 0;

	if (!m_font.loadFromFile("Orange Kid.otf")) {
		std::cerr << "Error: Cannot load font 'Orange Kid.otf'\n";
	}

	m_player.setTexture(loadTexture("player.png"));
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

const sf::Texture& GameManager::loadTexture(const std::string& texturePath) {
	// Check if the texture is already loaded
	if (m_textures.find(texturePath) == m_textures.end()) {
		// Load the texture and store it
		sf::Texture texture;
		if (!texture.loadFromFile(texturePath)) {
			std::cerr << "Error loading texture: " << texturePath << "\n";
		}
		m_textures[texturePath] = std::move(texture);
	}
	return m_textures[texturePath];
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

    //set window size based on level
	int windowWidth = numCols * m_tileSize;
	int windowHeight = (numRows * m_tileSize); 
	m_window.create(sf::VideoMode(windowWidth, windowHeight + m_tileSize), "Bomberman");
	m_width = windowWidth;
	m_height = windowHeight + m_tileSize;

	m_board.resize(numRows);
	for (auto& row : m_board) {
		row.resize(numCols, nullptr);
	}

	for (int row = 0; row < numRows; ++row) {
		for (int col = 0; col < numCols; ++col) {
			char tile = lines[row][col];
			GameObject* gameObject = nullptr;
			Guard* g = nullptr;

			switch (tile) {
			
			case '#':
				gameObject = new Wall(col * m_tileSize, m_tileSize + row * m_tileSize, m_window);
				gameObject->setTexture(loadTexture("wall.png"));
				break;
			case '@':
				gameObject = new Rock(col * m_tileSize, m_tileSize + row * m_tileSize, m_window);
				gameObject->setTexture(loadTexture("rock.png"));
				break;
			case 'D':
				gameObject = new Door(col * m_tileSize, m_tileSize + row * m_tileSize, m_window);
				gameObject->setTexture(loadTexture("door.png"));
                m_currLeveldoor = dynamic_cast<Door*>(gameObject);
				break;
			case '!':
				g = new Guard(m_window, sf::Vector2f(col * m_tileSize, m_tileSize + row * m_tileSize));
				g->setTexture(loadTexture("guard.png"));
				g->setType(GUARD);
				m_guards.push_back(g);
				break;
			default:
				break;
			}

			m_board[row][col] = gameObject;
			if (gameObject) {
				if (!gameObject->getSprite().getTexture()) {
					std::cerr << "Error: object texture not set properly.\n";
				}
			}
		}
	}
	if (!m_guards.empty())
		m_levelNumGuards = m_guards.size();
}

void GameManager::mainMenuScreen()
{
	int menuSize = 500;
	m_window.create(sf::VideoMode(menuSize, menuSize), "Bomberman Main Menu");
	sf::Font font;
	if (!font.loadFromFile("Orange Kid.otf"))
	{ 
		std::cerr << "Cannot load font\n";
	}

	sf::Text play;
	play.setFont(font);
	play.setFillColor(sf::Color::Black);
	play.setString("PLAY");
	play.setCharacterSize(150);
	int centerX = (menuSize / 2) - play.getGlobalBounds().width / 2;
	int centerY = (menuSize / 2) - play.getGlobalBounds().height;
	play.setPosition(sf::Vector2f(centerX,centerY - 20));

	
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
						runGame();
					}
				}
				break;
			default:
				break;
			}
		}

		m_window.clear(sf::Color::White);
		m_window.draw(play);
		m_window.display();
	}
}

void GameManager::toolbar()
{
	m_livesText.setFont(m_font);
	m_scoreText.setFont(m_font);
	m_levelText.setFont(m_font);
	m_helpText.setFont(m_font);
	m_exitText.setFont(m_font);
	m_timeText.setFont(m_font);

	m_livesText.setFillColor(sf::Color::Black);
	m_scoreText.setFillColor(sf::Color::Black);
	m_levelText.setFillColor(sf::Color::Black);
	m_helpText.setFillColor(sf::Color::Black);
	m_exitText.setFillColor(sf::Color::Black);
	m_timeText.setFillColor(sf::Color::Black);

	m_livesText.setCharacterSize(70);
	m_scoreText.setCharacterSize(70);
	m_levelText.setCharacterSize(70);
	m_helpText.setCharacterSize(70);
	m_exitText.setCharacterSize(70);
	m_timeText.setCharacterSize(70);

	int toolbarY = 2;
	int toolbarX = 0;
	m_levelText.setPosition(sf::Vector2f(toolbarX, toolbarY));
	m_livesText.setPosition(sf::Vector2f(toolbarX + (5 *m_tileSize), toolbarY));
	m_scoreText.setPosition(sf::Vector2f(toolbarX + (10 * m_tileSize), toolbarY));
	m_timeText.setPosition(sf::Vector2f(toolbarX + (15 * m_tileSize), toolbarY));
	m_helpText.setPosition(sf::Vector2f(toolbarX + (20 * m_tileSize), toolbarY));
	m_exitText.setPosition(sf::Vector2f(toolbarX + (25 * m_tileSize), toolbarY));

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
	m_helpText.setString("Help");
	m_exitText.setString("Exit");

	int minutes = m_clock.getElapsedTime().asSeconds() / 60;
	int seconds = int(m_clock.getElapsedTime().asSeconds()) % 60;
	if(seconds < 10)
		m_timeText.setString("Time: " + std::to_string(minutes) + ":0" + std::to_string(seconds));
	else
		m_timeText.setString("Time: " + std::to_string(minutes) + ":" + std::to_string(seconds));

	m_window.draw(m_livesText);
	m_window.draw(m_scoreText);
	m_window.draw(m_levelText);
	m_window.draw(m_helpText);
	m_window.draw(m_exitText);
	m_window.draw(m_timeText);
}

void GameManager::drawBombs(std::vector<Bomb*>& m_bombs)
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
				m_bombs[i]->setTexture(loadTexture("bomb1.png"));
				break;
			case 1:
				m_bombs[i]->setTexture(loadTexture("bomb1.png"));
				break;
			case 2:
				m_bombs[i]->setTexture(loadTexture("bomb2.png"));
				break;
			case 3:
				m_bombs[i]->setTexture(loadTexture("bomb3.png"));
				break;
			case 4:
				m_bombs[i]->setTexture(loadTexture("bomb4.png"));
				break;
			case 5:
				m_bombs[i]->setTexture(loadTexture("explosion.png"));
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
				delete m_bombs[i];
				m_bombs[i] = nullptr; // Avoid dangling pointer
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
	if (!m_guards.empty())
	{
		delete m_guards[i];
		m_guards[i] = nullptr;
		m_guards.erase(m_guards.begin() + i);
	}
	m_score += 5;
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
		while (m_currLevel != 4)
		{
			// Load level
			drawLevel(m_currLevel); //TODO: delete m_guards at the start of each new level
			m_window.setFramerateLimit(60);
			m_player.respawn();

			//add toolbar
			toolbar();

			sf::Clock clock;

			// Main game loop
			while (m_window.isOpen())
			{

				// Calculate delta time for this frame
				const auto deltaTime = clock.restart();

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
							Bomb* b = new Bomb(m_window, m_player.getSprite().getPosition().x, m_player.getSprite().getPosition().y);
							m_bombs.push_back(b);
						}
						else
							m_player.setDirection(event.key.code);

						break;

					default:
						break;
					}
				}

				// Update game state
				if (m_player.getLives() == 0)
				{
					//TODO: game over screen and exit
				}

				m_player.move(deltaTime, m_board, m_player);

				for (auto& guard : m_guards) {
					guard->move(deltaTime, m_board, m_player);
				}

				if (m_currLeveldoor->getPassed())
				{
					m_score = 25 + (3 * m_levelNumGuards);
					m_currLevel++;
					m_window.close();
				}

				// Render the scene
				m_window.clear(sf::Color::White);
				drawBoard();
				drawGuards();
				m_player.draw();
				if (!m_bombs.empty())
					drawBombs(m_bombs);
				drawToolbar();
				m_window.display();
			}
		}
		//TODO: you win screen function with exit button
	}
}