#pragma once

#include <vector>
#include <memory>
#include "util/Window.h"
#include "util/Timer.h"
#include "graphics/Renderer.h"
#include "Board.h"

namespace
{
	const glm::vec4 COL_WHITE(1.0f);
}

class Game
{
public:

	static const int SQUARE_SIZE = 5;
	static const int SQuARE_OFFSET = 0;
	static const int WIN_SIZE_WIDTH = SQUARE_SIZE * Board::ROW_LENGTH;
	static const int WIN_SIZE_HEIGHT = SQUARE_SIZE * Board::COL_LENGTH;

	Game();
	~Game();

	void keyCallback(int keycode, bool released, bool repeated);
	void run();

private:

	void init();
	void dispose();
	void draw();
	void update();

	std::unique_ptr<Window> mWin;
	std::unique_ptr<Timer> mTimer;
	std::unique_ptr<Renderer> mRenderer;

	bool mRun = true;
	bool mStep = false;
	bool mIterate = false;

	std::unique_ptr<Board> mBoard;
	std::vector<bool> mBoardBuffer;

};

