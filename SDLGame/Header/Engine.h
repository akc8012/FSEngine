#pragma once
#include "Renderer.h"
#include <SDL.h>

class Engine
{
private:
	static const int WindowStartWidth = 480, WindowStartHeight = 320;

	SDL_Window* window = NULL;
	Renderer* renderer = NULL;

	SDL_Window* createWindow(int width = WindowStartWidth, int height = WindowStartHeight);
	
	void setFullscreen();
	void setWindowed();

	void update();

public:
	~Engine();

	bool init();
	void handleKeyboardEvent(SDL_KeyboardEvent keyboardEvent);
	void handleWindowEvent(SDL_WindowEvent windowEvent);
	void run();
};
