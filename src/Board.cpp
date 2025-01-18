#include "Board.h"

Board::Board()
{
	m_row = 0;
	m_col = 0;
	m_board.resize(100, std::vector<sf::Sprite>(100));
}

void Board::drawLevel(sf::RenderWindow& window, const std::string& fileName) {

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

    // Read the file into lines to determine the size
    std::vector<std::string> lines;
    std::string line;
    while (std::getline(file, line)) 
    {
        lines.push_back(line);
    }

    // Initialize board dimensions
    int numRows = lines.size();
    int numCols = lines.empty() ? 0 : lines[0].size();
    m_board.resize(numRows, std::vector<sf::Sprite>(numCols));
 
    // Reset the file stream to the beginning
    file.clear();
    file.seekg(0, std::ios::beg);

    // Parse the file and draw the board
    int row = 0;

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
				m_board[row][col] = *sprite;
            }
        }
        ++row;
    }

    //draw
    m_row = numRows;
    m_col = numCols;
	for (int row = 0; row < m_row; ++row) {
		for (int col = 0; col < m_col; ++col) {
			window.draw(m_board[row][col]);
		}
	}  
}

sf::Vector2f Board::getTilePosition(int row, int col)
{
    if (!(m_board.empty() || row < 0 || row >= m_row || col < 0 || col >= m_col))
    {
        return m_board[row][col].getPosition();
    }
    else
        return sf::Vector2f(-1,-1);
}

sf::Texture* Board::getTexture(sf::Vector2f position)
{
	if (!(m_board.empty()))
	{
		for (int row = 0; row < m_row; ++row) {
			for (int col = 0; col < m_col; ++col) {
				if (m_board[row][col].getPosition() == position)
				{
					//return m_board[row][col].getTexture();
                    return nullptr;
				}
			}
		}
	}
	return nullptr; // Return nullptr if no texture is found
}
