#pragma once
#include <SDL.h>

class Engine
{
private:
	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;

	SDL_Window* window = NULL;
	SDL_Surface* screenSurface = NULL;
	SDL_Surface* helloWorldSurface = NULL;

	SDL_Window* createWindow();
	void loadMedia();

public:
	bool init();
	void handleInput(SDL_Event& event);
	void run();
	void quit();
};
