#pragma once
#include "Renderer.h"
#include <SDL.h>

class Engine
{
private:
	SDL_Window* window = NULL;
	Renderer* renderer = NULL;

	SDL_Window* createWindow(int screenWidth = 480, int screenHeight = 320);

	void update();

public:
	~Engine();

	bool init();
	void handleKeyboardEvent(SDL_KeyboardEvent keyboardEvent);
	void handleWindowEvent(SDL_WindowEvent windowEvent);
	void run();
};
