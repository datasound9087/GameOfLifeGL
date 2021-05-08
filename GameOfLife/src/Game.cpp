#include "Game.h"
#include "graphics/BatchRenderer.h"
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

Game::Game()
{
}


Game::~Game()
{
}

void Game::keyCallback(int keycode, bool released, bool repeated)
{
	if(!repeated && !released)
	{
		if(keycode == SDLK_ESCAPE)
		{
			mRun = false;
		//space key
		}else if(keycode == SDLK_SPACE)
		{
			mStep = mIterate ? false : true;
		}
		//backspace key
		else if (keycode == SDLK_BACKSPACE)
		{
			mIterate = !mIterate;
		}
	}
}

void Game::run()
{
	init();
	Timer timer;

	float time = 0.0f;
	float updateTimer = 0.0f;
	float updateTick = 1.0f / 15.0f;

	unsigned int frames = 0;
	unsigned int updates = 0;

	while (mRun)
	{
		mWin->pollEvents();

		if(mWin->shouldClose()) mRun = false;

		if (timer.timeElapsed() - updateTimer > updateTick)
		{
			update();
			updates++;
			updateTimer += updateTick;
		}

		mWin->clearBuffers();
		draw();
		mWin->swapBuffers();

		frames++;
		if (timer.timeElapsed() - time > 1.0f)
		{
			//tick();
			time += 1.0f;
			//m_FPS = frames;
			//m_UPS = updates;

			updates = 0;
			frames = 0;
		}
	}

	mWin->dispose();
}

void Game::init()
{
	mWin = std::make_unique<Window>("Game of Life", WIN_SIZE_WIDTH, WIN_SIZE_HEIGHT);
	mWin->setKeyCallback(std::bind(&Game::keyCallback, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
	mRenderer = std::make_unique<BatchRenderer>(glm::ortho(0.0f, static_cast<float>(WIN_SIZE_WIDTH), 0.0f, static_cast<float>(WIN_SIZE_HEIGHT)));
	mRenderer->init();

	mBoard = std::make_unique<Board>();
	mBoard->fillRandom();
	mWin->setVisible(true);
}

void Game::dispose()
{

}

void Game::draw()
{
	mRenderer->begin();

	if(mBoard->hasUpdated())
	{
		mBoardBuffer = mBoard->getBoard();
	}

	uint32_t i = 0;
	for (float y = 0.0f; y < WIN_SIZE_HEIGHT; y += SQUARE_SIZE + SQuARE_OFFSET)
	{
		for (float x = 0.0f; x < WIN_SIZE_WIDTH; x += SQUARE_SIZE + SQuARE_OFFSET)
		{
			if (mBoardBuffer[i])
			{
				mRenderer->submit(glm::vec2(x, y), glm::vec2(SQUARE_SIZE), COL_WHITE);
			}
			i++;
		}
	}

	mRenderer->end();
	mRenderer->flush();
}

void Game::update()
{
	if (mStep)
	{
		mBoard->step();
		mStep = false;
	}
	else if (mIterate)
	{
		mBoard->step();
	}
}

///////////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[])
{
	Game game;
	game.run();

	return 0;
}