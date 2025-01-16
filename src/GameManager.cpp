#include "GameManager.h"

void GameManager::runGame()
{
    
    //backround
    sf::Texture gameBackround;
    gameBackround.loadFromFile("gameBackround.png");
    sf::Sprite gameBackroundSprite(gameBackround);

	//window handling
	while (m_window.isOpen())
	{

		if (auto event = sf::Event{}; m_window.waitEvent(event))
		{
			m_window.clear(sf::Color::White);
			m_window.draw(gameBackroundSprite);
            drawLevel(m_window, "level001.txt");
			m_window.display();
			switch (event.type)
			{
			case sf::Event::Closed:
				m_window.close();
				break;
			}
		}

	}
}

bool GameManager::openLevel(int i)
{
	auto currentLevel = std::ifstream(m_levels[i]);
	if (!currentLevel) {
		std::cerr << "Cannot open level " << m_levels[i] << "\n";
		return false;
	}
	std::cout << "Opened level " << m_levels[i] << "\n";
	m_currentLevelName = m_levels[i];
	m_currentLevelIndex = i;
	return true;
}

void GameManager::drawLevel(sf::RenderWindow& window, const std::string& fileName) const {

    std::ifstream file(fileName);
    if (!file) {
        std::cerr << "Cannot open level file: " << fileName << "\n";
        return;
    }

    // Load textures for sprites
    sf::Texture wallTexture, rockTexture, doorTexture;
    if (!wallTexture.loadFromFile("wall.png") ||
        !rockTexture.loadFromFile("rock.png") ||
        !doorTexture.loadFromFile("door.png")) {
        std::cerr << "Failed to load one or more textures.\n";
        return;
    }

    // Prepare reusable sprites
    sf::Sprite wallSprite(wallTexture);
    sf::Sprite rockSprite(rockTexture);
    sf::Sprite doorSprite(doorTexture);

    // Parse the file and draw the board

    int row = 0;
    std::string line;

    while (std::getline(file, line)) {
        for (int col = 0; col < line.size(); ++col) {
            char tile = line[col];
            sf::Sprite* sprite = nullptr;

            // Determine which sprite to use based on the character
            switch (tile) {
            case '#':
                sprite = &wallSprite;
                break;
            case '@':
                sprite = &rockSprite;
                break;
            case 'D':
                sprite = &doorSprite;
                break;
            default:
                // Skip unknown tiles
                continue;
            }

            // Set sprite position and draw it
            if (sprite) {
                sprite->setPosition(col * m_tileSize, row * m_tileSize + m_toolbarHeight);
                window.draw(*sprite);
            }
        }
        ++row;
    }

}
