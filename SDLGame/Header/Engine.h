#pragma once
#include "Renderer.h"
#include <SDL.h>

class Engine
{
private:
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
