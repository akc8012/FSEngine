#pragma once
#include "Window.h"
#include "ShaderProgram.h"
#include "Renderer.h"
#include "Timer.h"

#include <SDL.h>
#include <SDL_image.h>
#include <GL\glew.h>
#include <SDL_opengl.h>
#include <GL\GLU.h>

#include <string>
using namespace std;

class Engine
{
private:
	bool running = false;

	Window* window = NULL;
	ShaderProgram* shaderProgram = NULL;
	Renderer* renderer = NULL;

	void InitSDL();
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
