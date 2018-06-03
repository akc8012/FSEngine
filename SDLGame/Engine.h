#pragma once
#include <SDL.h>

class Engine
{
private:
	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;

	SDL_Window* window;

	SDL_Window* createWindow();

public:
	bool init();
	void quit();
};
