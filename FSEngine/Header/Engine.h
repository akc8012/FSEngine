#pragma once
#include "Window.h"
#include "ShaderProgram.h"
#include "Renderer.h"
#include "Timer.h"

#include <SDL.h>
#include <SDL_image.h>
#include <GL\glew.h>
#include <SDL_opengl.h>

#include <string>
using namespace std;

class Engine
{
private:
	bool running = false;
	Uint32 lastFrameStamp = 0;
	Uint32 deltaTime = 0;

	Window* window = NULL;
	ShaderProgram* shaderProgram = NULL;
	Renderer* renderer = NULL;

	void InitSDL();
	void InitOpenGl();
	void InitGlew();

	void ToggleSwapInterval();
	void SetSwapInterval(int interval);

	void PollEvents();
	void Update();
	void Draw();

	void HandleKeyboardEvent(const SDL_KeyboardEvent& keyboardEvent);
	void HandleWindowEvent(const SDL_WindowEvent& windowEvent);
	void CalculateDeltaTime();

public:
	~Engine();

	bool IsRunning();
	bool Init();

	void GameLoop();
};
