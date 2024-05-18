#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
using namespace std;

const int TILE_SIZE = 30;
const int ROWS = 20;
const int COLUMNS = 10;

class I_Tetromino
{
private:
	char m_rotoationState1[4][4] =
		{
			{'I', 'I', 'I', 'I'},
			{'0', '0', '0', '0'},
			{'0', '0', '0', '0'},
			{'0', '0', '0', '0'}};
	char m_rotoationState2[4][4] =
		{
			{'0', '0', '0', 'I'},
			{'0', '0', '0', 'I'},
			{'0', '0', '0', 'I'},
			{'0', '0', '0', 'I'}};

	char m_rotoationState3[4][4] =
		{
			{'0', '0', 'I', '0'},
			{'0', '0', 'I', '0'},
			{'0', '0', 'I', '0'},
			{'0', '0', 'I', '0'}};

	char m_rotoationState4[4][4] =
		{
			{'0', 'I', '0', '0'},
			{'0', 'I', '0', '0'},
			{'0', 'I', '0', '0'},
			{'0', 'I', '0', '0'}};

	char m_rotoationState5[4][4] =
		{
			{'I', '0', '0', '0'},
			{'I', '0', '0', '0'},
			{'I', '0', '0', '0'},
			{'I', '0', '0', '0'}};

public:
	char getRotationState1(int x, int y)
	{
		return m_rotoationState1[y][x];
	}
};
class O_Tetromino
{
};

class T_Tetromino
{
};

class S_Tetromino
{
};

class Z_Tetromino
{
};

class L_Tetromino
{
};

class J_Tetromino
{
};

class Board
{
private:
	char m_boardState[10][20];

public:
	void initializeNewEmptyBoard();
	void drawBoard(sf::RenderWindow &window);
	void initializeNewTetromino(I_Tetromino tetromino, int size, int offsetFromCenter);
	void moveFallingPieceDown();
	void keyboardActions(sf::Event event, int size);
	void lockFallingPieces();
};

int main()
{
	sf::RenderWindow window(sf::VideoMode(COLUMNS * TILE_SIZE, ROWS * TILE_SIZE), "Spel");
	// S�tt framerate till 60
	window.setFramerateLimit(20);

	Board theBoard;
	theBoard.initializeNewEmptyBoard();
	I_Tetromino the_I_tetromino;

	theBoard.initializeNewTetromino(the_I_tetromino, 4, 3); // TEMP hårdkodning!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	int currentFrame = 0;
	while (window.isOpen())
	{

		sf::Event event;
		// Inv�nta ett event, allts� att vi g�r n�got
		while (window.pollEvent(event))
		{

			if (event.type == sf::Event::Closed)
				window.close();
		}
		theBoard.drawBoard(window);
		theBoard.lockFallingPieces();
		window.display();
		theBoard.keyboardActions(event, 4);
		if (currentFrame % 20 == 0)
		{
			theBoard.moveFallingPieceDown();
		}

		currentFrame++;
		theBoard.drawBoard(window);
	}
	return 0;
}

void Board::initializeNewEmptyBoard()
{
	for (int x = 0; x < 10; x++)
	{
		for (int y = 0; y < 20; y++)
		{
			m_boardState[x][y] = '0';
		}
	}
}

void Board::drawBoard(sf::RenderWindow &window)
{
	for (int x = 0; x < 10; x++)
	{
		for (int y = 0; y < 20; y++)
		{
			if (m_boardState[x][y] == 'I')
			{
				sf::RectangleShape block(sf::Vector2f(TILE_SIZE, TILE_SIZE));
				block.setPosition(x * TILE_SIZE, y * TILE_SIZE);
				block.setFillColor(sf::Color::Blue);
				window.draw(block);
			}
			else if (m_boardState[x][y] == '1')
			{
				sf::RectangleShape block(sf::Vector2f(TILE_SIZE, TILE_SIZE));
				block.setPosition(x * TILE_SIZE, y * TILE_SIZE);
				block.setFillColor(sf::Color::Black);
				window.draw(block);
			}
			else
			{
				sf::RectangleShape block(sf::Vector2f(TILE_SIZE, TILE_SIZE));
				block.setPosition(x * TILE_SIZE, y * TILE_SIZE);
				block.setFillColor(sf::Color::Green);
				window.draw(block);
			}
		}
	}
}

void Board::initializeNewTetromino(I_Tetromino tetromino, int size, int offsetFromCenter)
{
	for (int y = 0; y < size; y++)
	{
		for (int x = 0; x < size; x++)
		{
			char temp = tetromino.getRotationState1(x, y);
			m_boardState[x + offsetFromCenter][y] = temp;
		}
	}
}

void Board::moveFallingPieceDown()
{
	int movedSpaces = 0;
	char temp;
	for (int y = 19; y >= 0; y--)
	{
		for (int x = 0; x < 10; x++)
		{
			if (y == 19)
			{
				break;
			}

			if (m_boardState[x][y] != '0' && m_boardState[x][y + 1] == '0')
			{
				char temp = m_boardState[x][y];
				m_boardState[x][y + 1] = temp;
				m_boardState[x][y] = '0';
			}
		}
	}
}

void Board::lockFallingPieces()
{
	for (int x = 0; x < 10; x++)
	{
		if (m_boardState[x][19] != '0' && m_boardState[x][19] != '1')
		{
			for (int y = 15; y < 20; y++)
			{
				for (int xx = 0; xx < 10; xx++) // om en bit slår i botten behöver jag aldrig kontrollera mer än 4 rutor ovanför
				{								// Variabelnamnet x var redan taget
					if (m_boardState[xx][y] != '0' && m_boardState[xx][y] != '1')
					{
						m_boardState[xx][y] = '1';
					}
				}
			}
			return;
		}
	}
}

void Board::keyboardActions(sf::Event event, int size)
{
	// SIDE-MOVEMENT
	bool keepGoing = true;
	int x_value = 0;
	int y_value = 0;
	int x_start;
	int x_end;
	char temp;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		for (int y = 0; y < 19; y++)
		{
			if (m_boardState[0][y] != '0' && m_boardState[0][y] != '1')
			{
				keepGoing = false;
			}
		}
		if (keepGoing = true) // skippa foljande block om biten redan e i kanten
		{
			for (int y = 0; y < 19; y++)
			{
				for (int x = 0; x < 10; x++)
				{
					if (m_boardState[x][y] != '0' && m_boardState[x][y] != '1')
					{
						x_value = x; // identifiera x && y i ovre-vanstra hornet pa biten.
						y_value = y;
						keepGoing = false; // 2 "break" behovs for nestlade loopar, detta
						break;			   // e for detta
					}
				}
				if (keepGoing == false)
				{
					break;
				}
			}

			if (x_value == 0)
			{
				return;
			}

			for (int row = 0; row < size; row++)
			{
				for (int column = 0; column < size; column++)
				{
					temp = m_boardState[x_value + row][y_value + column];
					m_boardState[x_value + row][y_value + column] = '0';
					m_boardState[x_value + row - 1][y_value + column] = temp;
				}
			}
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) // Same shit but right
	{
		for (int y = 0; y < 19; y++)
		{
			if (m_boardState[9][y] != '0' && m_boardState[9][y] != '1')
			{
				keepGoing = false;
			}
		}
		if (keepGoing = true) // skippa foljande block om biten redan e i kanten
		{
			for (int y = 0; y < 19; y++)
			{
				for (int x = 9; x >= 0; x--)
				{
					if (m_boardState[x][y] != '0' && m_boardState[x][y] != '1')
					{
						x_value = x; // identifiera x && y i ovre-vanstra hornet pa biten.
						y_value = y;
						keepGoing = false; // 2 "break" behovs for nestlade loopar, detta
						break;			   // e for detta
					}
				}
				if (keepGoing == false)
				{
					break;
				}
			}

			if (x_value == 9)
			{
				return;
			}

			for (int row = 0; row < size; row++)
			{
				for (int column = 0; column < size; column++)
				{
					temp = m_boardState[x_value - row][y_value + column];
					m_boardState[x_value - row][y_value + column] = '0';
					m_boardState[x_value - row + 1][y_value + column] = temp;
				}
			}
		}
	}
	// END SIDE-MOVEMENT

	keepGoing = true;
	// HARD-DROP
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		for (int y = 0; y < 19; y++)
		{
			for (int x = 0; x < 10; x++)
			{
				if (m_boardState[x][y] != '0' && m_boardState[x][y] != '1')
				{
					x_start = x;
					y_value = y;

					for (; x < 10; x++)
					{
						if (m_boardState[x][y] == '1' || m_boardState[x][y] == '0' || x == 9)
						{
							x_end = x - 1;
							if (x_start == 6)
							{
								x_end = 9;
							}
							break;
						}
					}
					// fanskapet fungerar inte
					int FuckedUpBeyondAllRecognition = 0;
					keepGoing = true;
					for (; y < 20; y++)
					{
						for (int x = x_start; x <= x_end; x++)
						{
							if (m_boardState[x][y] == '1' || y == 19)
							{
								FuckedUpBeyondAllRecognition = y;
								break;
								keepGoing = false;
							}
						}
						if (keepGoing == false)
						{
							break;
						}
					}

					cout << "start:\n"
						 << x_start << "\n"
						 << "end:\t" << x_end << "\n";
					for (int x = x_start; x <= x_end; x++)
					{
						temp = m_boardState[x][y_value];
						m_boardState[x][y_value] = '0';
						m_boardState[x][FuckedUpBeyondAllRecognition] = temp;
					}

					cout << FuckedUpBeyondAllRecognition;
					return;
				}
			}
		}
	}
	// END HARD-DROP
}