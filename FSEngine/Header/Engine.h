#pragma once
#include "Renderer.h"
#include "Window.h"
#include "Timer.h"
#include <SDL.h>

class Engine
{
private:
	Window* window = NULL;
	Renderer* renderer = NULL;
	Timer* timer;

public:
	~Engine();

	bool init();

	void handleWindowEvent(const SDL_WindowEvent& windowEvent);
	void handleKeyboardEvent(const SDL_KeyboardEvent& keyboardEvent);

	void run();
	void update();
};
