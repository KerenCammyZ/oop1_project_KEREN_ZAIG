#include "GameManager.h"

void GameManager::runGame()
{
    auto window = sf::RenderWindow(sf::VideoMode(2400, 1600), "Bomberman");

    //textures
    sf::Texture gameBackround;
    gameBackround.loadFromFile("gameBackround.png");
    sf::Sprite gameBackroundSprite(gameBackround);

    if (!openPlaylist()) {
        std::cerr << "Open Playlist failed. Exiting...\n";
    }

    if (m_levels.empty()) {
        std::cerr << "No levels found in Playlist.txt. Exiting...\n";
        return;
    }
    else
    {
        for (int i = 0; i < m_levels.size(); i++)
        {
            if (!openLevel(i))
            {
                std::cerr << "Open Level failed. Exiting...\n";
                return;
            }
            else
            {
                //run game
                std::cout << "Running level " << m_levels[i] << "\n";

                //set board


                //window handling
                while (window.isOpen())
                {
                    //print board
                    if (m_board.empty())
                    {
                        std::cerr << "No board found. Exiting...\n";
                        return;
                    }
                    else
                    {
                        for (int i = 0; i < m_board.size(); i++)
                        {
                            for (int j = 0; j < m_board[i].size(); j++)
                            {
                                window.draw(m_board[i][j]);
                            }
                        }

                        if (auto event = sf::Event{}; window.waitEvent(event))
                        {
                            window.clear(sf::Color::White);
                            window.draw(gameBackroundSprite);
                            window.display();
                            switch (event.type)
                            {
                            case sf::Event::Closed:
                                window.close();
                                break;
                            }
                        }
                    }
                }
            }
        }

    }
}

bool GameManager::openPlaylist()
{
    return false;
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

void GameManager::drawLevel(sf::RenderWindow& window, const std::string& fileName, int levelIndex) {

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
