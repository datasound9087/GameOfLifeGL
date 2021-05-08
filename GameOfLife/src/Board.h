#pragma once

#include <cstdint>
#include <vector>

class Board
{
public:

	static const uint32_t ROW_LENGTH = 120;
	static const uint32_t COL_LENGTH = 120;
	static const uint32_t BOARD_SIZE = ROW_LENGTH * COL_LENGTH;

	static const bool CELL_DEAD = false;
	static const bool CELL_ALIVE = true;

	Board();
	~Board();

	void step();
	void iterate(const uint32_t numSteps);

	void fillRandom();
	void fillOscillator();
	void fillGlider();

	bool hasUpdated();

	std::vector<bool>& getBoard();

private:

	uint32_t countNeighbours(uint32_t x, uint32_t y);
	inline void setCellAt(uint32_t x, uint32_t y, bool val);
	inline bool getCellAt(uint32_t x, uint32_t y);

	std::vector<bool> mBoard;

	bool mUpdated = true;
};

