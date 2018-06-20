#pragma once
#include "Window.h"
#include "ShaderProgram.h"
#include "Renderer.h"
#include <SDL.h>

class Engine
{
private:
	bool running = false;

	Window* window = NULL;
	SDL_GLContext context;
	ShaderProgram* shaderProgram = NULL;
	Renderer* renderer = NULL;

	void InitSDL();
	void CreateContext();
	void InitOpenGl();
	void InitGlew();

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
