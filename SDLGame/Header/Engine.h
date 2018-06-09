#pragma once
#include "Renderer.h"
#include <SDL.h>

class Engine
{
private:
	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;

	SDL_Window* window = NULL;
	Renderer* renderer = NULL;

	SDL_Window* createWindow();

	void update();

public:
	~Engine();

	bool init();
	void handleKeydown(SDL_Keycode keycode);
	void run();
};
