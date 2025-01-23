#include "GameManager.h"


//void GameManager::draw()
//{
//	if (m_window.isOpen() && !m_gameObjects.empty())
//	{
//		for (int i = 0; i < m_gameObjects.size(); i++)
//		{
//			if (!m_gameObjects[i].empty())
//			{
//				for (int j = 0; j < m_gameObjects[i].size(); j++)
//				{
//					//m_gameObjects[i][j].draw();
//				}
//			}
//		}
//	}
//	else 
//	{
//		drawLevel("level001.txt");
//	}
//}

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
    const_cast<GameManager*>(this)->m_height = numRows + m_tileSize;
    const_cast<GameManager*>(this)->m_width = numCols;

    // Reset the file stream to the beginning
    file.clear();
    file.seekg(0, std::ios::beg);

    // Parse the file and draw the window
	m_gameObjects.resize(numRows + 1);
    int row = 1;

	while (std::getline(file, line)) 
	{
		m_gameObjects[row].resize(numCols);
		for (int col = 0; col < line.size(); ++col)
		{
			char tile = line[col];
			GameObject* gameObject;
			switch (tile)
			{
			case '#':
				gameObject->setTexture("wall.png");
				break;
			case 'R':
				gameObject->setTexture("rock.png");
				break;
			case 'D':
				gameObject->setTexture("door.png");
				break;
			}
			m_gameObjects[row][col] = gameObject;
		}
		row++;
	}
}

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
			drawLevel("level001.txt");
			for (int i = 1; i < m_gameObjects.size(); i++)
			{
				for (int j = 0; j < m_gameObjects[i].size(); j++)
				{
					m_gameObjects[i][j]->draw();
				}
			}
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

