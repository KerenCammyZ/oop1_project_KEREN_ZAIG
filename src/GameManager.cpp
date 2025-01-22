#include "GameManager.h"


void GameManager::drawLevel(const std::string& fileName) const
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
    
    // Reset the file stream to the beginning
    file.clear();
    file.seekg(0, std::ios::beg);


    //draw the toolbar
    

    //// Parse the file and draw the board
    //int row = 0;

    //while (std::getline(file, line))
}

//void GameManager::runGame()
//{
//    
//    //backround
//    sf::Texture gameBackround;
//    gameBackround.loadFromFile("gameBackround.png");
//    sf::Sprite gameBackroundSprite(gameBackround);
//
//	//window handling
//	while (m_window.isOpen())
//	{
//
//		if (auto event = sf::Event{}; m_window.waitEvent(event))
//		{
//			m_window.clear(sf::Color::White);
//			m_window.draw(gameBackroundSprite);
//			m_board.drawLevel(m_window, "level001.txt");
//			m_player.drawPlayer(m_window);
//			m_window.display();
//			switch (event.type)
//			{
//			case sf::Event::Closed:
//				m_window.close();
//				break;
//			case sf::Event::KeyPressed:
//				switch (event.key.code)
//				{
//				case sf::Keyboard::Up:
//					m_player.movePlayer(0, -1, m_board);
//					break;
//				case sf::Keyboard::Down:
//					m_player.movePlayer(0, 1, m_board);
//					break;
//				case sf::Keyboard::Left:
//					m_player.movePlayer(-1, 0, m_board);
//					break;
//				case sf::Keyboard::Right:
//					m_player.movePlayer(1, 0, m_board);
//					break;
//				}
//				break;
//			}
//		}
//
//	}
//}

