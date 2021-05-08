#include "Board.h"

#include <random>
#include <iostream>

Board::Board()
{
	mBoard.resize(BOARD_SIZE);
}

Board::~Board()
{

}

void Board::step()
{
	//store updated cell indexes
	std::vector<uint32_t> died;
	std::vector<uint32_t> alive;

	for(uint32_t y = 0; y < COL_LENGTH; y++)
	{
		for(uint32_t x = 0; x < ROW_LENGTH; x++)
		{
			uint32_t numNeighbours = countNeighbours(x, y);
			/*Any live cell with fewer than two live neighbours dies, as if by underpopulation.
			Any live cell with two or three live neighbours lives on to the next generation.
			Any live cell with more than three live neighbours dies, as if by overpopulation.
			Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.*/
			if (getCellAt(x, y))
			{
				if (numNeighbours < 2 || numNeighbours > 3)
				{
					died.push_back(y * ROW_LENGTH + x);
					mUpdated = true;
				}
			}
			else
			{
 				if (numNeighbours == 3)
				{
					alive.push_back(y * ROW_LENGTH + x);
					mUpdated = true;
				}
			}
		}
	}

	//update cells
	for (uint32_t i : died)
	{
		mBoard[i] = CELL_DEAD;
	}

	for (uint32_t i : alive)
	{
		mBoard[i] = CELL_ALIVE;
	}
}

void Board::iterate(const uint32_t numSteps)
{
	for(uint32_t i = 0; i < numSteps; i++)
	{
		step();
	}
}

void Board::fillRandom()
{
	std::random_device dev;
	std::mt19937 rand(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist(0, 1);

	for(uint32_t i = 0; i < mBoard.size(); i++)
	{
		mBoard[i] = dist(rand);
	}
}

void Board::fillOscillator()
{
	//3 by 3 stable oscillator
	setCellAt(10, 10, CELL_ALIVE);
	setCellAt(10, 11, CELL_ALIVE);
	setCellAt(10, 12, CELL_ALIVE);
}

void Board::fillGlider()
{
	//glider
	setCellAt(30, 30, CELL_ALIVE);
	setCellAt(31, 30, CELL_ALIVE);
	setCellAt(32, 30, CELL_ALIVE);
	setCellAt(30, 29, CELL_ALIVE);
	setCellAt(31, 28, CELL_ALIVE);
}

bool Board::hasUpdated()
{
	return mUpdated;
}

std::vector<bool>& Board::getBoard()
{
	mUpdated = false;
	return mBoard;
}

uint32_t Board::countNeighbours(uint32_t x, uint32_t y)
{
	int minX = x == 0 ? 0 : -1;
	int maxX = x + 1 == ROW_LENGTH ? 0 : 1;

	int minY = y == 0 ? 0 : -1;
	int maxY = y + 1 == COL_LENGTH ? 0 : 1;

	uint32_t count = 0;

	for(int offsetY = minY; offsetY <= maxY; offsetY++)
	{
		for(int offsetX = minX; offsetX <= maxX; offsetX++)
		{
			if(offsetY == 0 && offsetX == 0) continue; //reading is a preferable skill :) not checking x or y

			count += getCellAt(x + offsetX, y + offsetY);
		}
	}

	return count;
}

inline bool Board::getCellAt(uint32_t x, uint32_t y)
{
	return mBoard[y * ROW_LENGTH + x];
}

inline void Board::setCellAt(uint32_t x, uint32_t y, bool val)
{
	mBoard[y * ROW_LENGTH + x] = val;
}
