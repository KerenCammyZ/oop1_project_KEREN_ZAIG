#include "GameManager.h"
#include "Guard.h"

GameManager::GameManager() : m_player(m_window, sf::Vector2f(m_tileSize, m_tileSize)) {
	m_width = 0;
	m_height = 0;

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

void GameManager::draw()
{
	if (m_window.isOpen() && !m_board.empty()) {
		for (const auto& row : m_board) {
			for (const auto& obj : row) {
				if (obj) { 
					obj->draw();
				}
			}
		}
	}
}

void GameManager::drawLevel(const std::string& fileName)
{
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

			switch (tile) {
			
			case '#':
				gameObject = new GameObject(m_window, sf::Vector2f(col * m_tileSize, row * m_tileSize));
				gameObject->setTexture(loadTexture("wall.png"));
				gameObject->setType("wall");
				break;
			case '@':
				gameObject = new GameObject(m_window, sf::Vector2f(col * m_tileSize, row * m_tileSize));
				gameObject->setTexture(loadTexture("rock.png"));
				gameObject->setType("rock");
				break;
			case 'D':
				gameObject = new GameObject(m_window, sf::Vector2f(col * m_tileSize, row * m_tileSize));
				gameObject->setTexture(loadTexture("door.png"));
				gameObject->setType("door");
				break;
			case '!':
				gameObject = new Guard(m_window, sf::Vector2f(col * m_tileSize, row * m_tileSize));
				gameObject->setTexture(loadTexture("guard.png"));
				gameObject->setType("guard");
				m_guards.push_back(dynamic_cast<Guard*>(gameObject));
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
}

void GameManager::runGame() 
{
	// Load level
	drawLevel("level001.txt");
	m_window.setFramerateLimit(60);

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
				break;

			case sf::Event::KeyPressed:
				m_player.setDirection(event.key.code);
				break;

			default:
				break;
			}
		}

		// Update game state
		m_player.move(deltaTime, m_board);
		for (auto& guard : m_guards) {
			guard->move(deltaTime, m_board);
		}
		// Render the scene
		m_window.clear(sf::Color::White);
		draw();          //draw level objects
		m_player.draw(); 
		m_window.display();
	}
}