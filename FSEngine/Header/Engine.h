#pragma once
#include "Renderer.h"
#include "Window.h"
#include <SDL.h>

class Engine
{
private:
	bool running = false;

	Window* window = NULL;
	Renderer* renderer = NULL;

	void handleWindowEvent(const SDL_WindowEvent& windowEvent);
	void handleKeyboardEvent(const SDL_KeyboardEvent& keyboardEvent);

public:
	~Engine();

	bool isRunning();
	bool init();

	void pollEvents();
	void update();
	void draw();
};
