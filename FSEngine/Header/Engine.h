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

	void HandleWindowEvent(const SDL_WindowEvent& windowEvent);
	void HandleKeyboardEvent(const SDL_KeyboardEvent& keyboardEvent);

public:
	~Engine();

	bool IsRunning();
	bool Init();

	void PollEvents();
	void Update();
	void Draw();
};
