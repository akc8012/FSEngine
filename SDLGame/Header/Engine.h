#pragma once
#include <SDL.h>

class Engine
{
private:
	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;

	SDL_Window* window = NULL;
	SDL_Surface* surface = NULL;
	SDL_Surface* helloWorldSurface = NULL;

	SDL_Window* createWindow();
	void loadMedia();

public:
	bool init();
	void run();
	void quit();
};
