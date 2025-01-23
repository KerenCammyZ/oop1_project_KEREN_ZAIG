#include "GameManager.h"


GameManager::GameManager()
{
	m_width = 0, m_height = 0, m_lives = 3, m_tileSize = 69;
}

GameManager::~GameManager() {
	for (auto& row : m_gameObjects) {
		for (auto& obj : row) {
			delete obj;
			obj = nullptr; // Avoid dangling pointers
		}
	}
	m_gameObjects.clear();
}

void GameManager::draw()
{
	if (m_window.isOpen() && !m_gameObjects.empty()) {
		for (const auto& row : m_gameObjects) {
			for (const auto& obj : row) {
				if (obj) { // Check for valid pointer
					obj->draw();
				}
			}
		}
	}
	//if (m_window.isOpen() && !m_gameObjects.empty())
	//{
	//	for (int i = 0; i < m_gameObjects.size(); i++)
	//	{
	//		if (!m_gameObjects[i].empty())
	//		{
	//			for (int j = 0; j < m_gameObjects[i].size(); j++)
	//			{
	//				m_gameObjects[i][j]->draw();
	//			}
	//		}
	//	}
	//}
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

	m_gameObjects.resize(numRows);
	for (auto& row : m_gameObjects) {
		row.resize(numCols, nullptr);
	}

	for (int row = 0; row < numRows; ++row) {
		for (int col = 0; col < numCols; ++col) {
			char tile = lines[row][col];
			GameObject* gameObject = nullptr;

			switch (tile) {
			case '#':
				gameObject = new GameObject(m_window, sf::Vector2f(col * m_tileSize, row * m_tileSize));
				gameObject->setTexture("wall.png");
				break;
			case 'R':
				gameObject = new GameObject(m_window, sf::Vector2f(col * m_tileSize, row * m_tileSize));
				gameObject->setTexture("wall.png");
				break;
			case 'D':
				gameObject = new GameObject(m_window, sf::Vector2f(col * m_tileSize, row * m_tileSize));
				gameObject->setTexture("door.png");
				break;
			}

			m_gameObjects[row][col] = gameObject;
		}
	}

 //   // Parse the file and draw the window
 //   int row = 1;

	//while (std::getline(file, line)) 
	//{
	//	m_gameObjects[row].resize(m_height);
	//	for (int col = 0; col < line.size(); ++col)
	//	{
	//		char tile = line[col];
	//		GameObject* gameObject = nullptr;
	//		
	//			switch (tile)
	//			{
	//			case '#':
	//				gameObject = new GameObject(m_window, sf::Vector2f(col * m_tileSize, row * m_tileSize));
	//				gameObject->setTexture("wall.png");
	//				break;
	//			case 'R':
	//				gameObject = new GameObject(m_window, sf::Vector2f(col * m_tileSize, row * m_tileSize));
	//				gameObject->setTexture("rock.png");
	//				break;
	//			case 'D':
	//				gameObject = new GameObject(m_window, sf::Vector2f(col * m_tileSize, row * m_tileSize));
	//				gameObject->setTexture("door.png");
	//				break;
	//			}
	//			m_gameObjects[row][col] = gameObject;
	//		}
	//	
	//	row++;
	//}
}

void GameManager::runGame()
{
    //backround
    sf::Texture gameBackround;
    gameBackround.loadFromFile("gameBackround.png");
    sf::Sprite gameBackroundSprite(gameBackround);
	//window
	//m_window.create(sf::VideoMode(1000, 1000), "Bomberman");
	drawLevel("level001.txt");
	//m_window.setFramerateLimit(60);

	//window handling
	while (m_window.isOpen())
	{

		if (auto event = sf::Event{}; m_window.waitEvent(event))
		{
			m_window.clear(sf::Color::White);
			m_window.draw(gameBackroundSprite);
			draw();

			
			/*for (int i = 1; i < m_gameObjects.size(); i++)
			{
				for (int j = 0; j < m_gameObjects[i].size(); j++)
				{
					m_gameObjects[i][j]->draw();
				}
			}*/
			m_window.display();
			switch (event.type)
			{
			case sf::Event::Closed:
				m_window.close();
				break;
			/*case sf::Event::KeyPressed:
				switch (event.key.code)
				{
				case sf::Keyboard::Up:
					m_player.movePlayer(0, -1, m_board);
					break;
				case sf::Keyboard::Down:
					m_player.movePlayer(0, 1, m_board);
					break;
				case sf::Keyboard::Left:
					m_player.movePlayer(-1, 0, m_board);
					break;
				case sf::Keyboard::Right:
					m_player.movePlayer(1, 0, m_board);
					break;
				}
				break;*/
			}
		}

	}
}

