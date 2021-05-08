#pragma once

#include <string>
#include <functional>
#include <SDL.h>

class Window
{
	//void key_callback(window* win, int keycode, bool released)
	typedef std::function<void(int, bool, bool)> KeyFunction;

	//void mousebutton_callback(windo* win, int keycode, bool relreased)
	typedef std::function<void(Window*, int, bool)> MouseButtonFunction;

	//void mouseMoved_callback(window* win, int x, int y)
	typedef std::function<void(Window*, int, int, int, int)> MouseMotionFunction;

public:
	Window(const std::string& name, int width, int height, bool vsync = false);
	~Window();

	void dispose();
	void setVisible(bool visible);
	void setVync(bool swap);

	void pollEvents();

	bool shouldClose();

	void setKeyCallback(const KeyFunction &func);

	void setMouseButtonCallback(const MouseButtonFunction &func);

	void setMouseMotionCallback(const MouseMotionFunction &func);

	void clearBuffers();

	void swapBuffers();

	SDL_Window* getSDLWindow() const;

private:

	int m_Width;
	int m_Height;
	
	std::string m_Name;

	KeyFunction m_KeyCallack = nullptr;
	MouseButtonFunction m_MouseButtonCallback = nullptr;
	MouseMotionFunction m_MouseMotionCallback = nullptr;

	bool m_Visible = false;
	bool m_Vsync = true;
	bool m_ShouldClose = false;

	SDL_Window* m_Win;
	SDL_GLContext m_Context;
};

