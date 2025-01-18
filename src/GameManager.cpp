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
			m_board.drawLevel(m_window, "level001.txt");
			m_player.drawPlayer(m_window);
			m_window.display();
			switch (event.type)
			{
			case sf::Event::Closed:
				m_window.close();
				break;
			case sf::Event::KeyPressed:
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
				break;
			}
		}

	}
}
