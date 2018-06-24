#pragma once
#include <SDL.h>
#include <GL\glew.h>
#include <SDL_opengl.h>

#include <glm/glm.hpp>
using namespace glm;

#include <string>
using namespace std;

class Window
{
private:
	static const int StartWidth = 800, StartHeight = 600;

	SDL_Window* window = NULL;
	SDL_GLContext context;

	void CreateWindow(int width = StartWidth, int height = StartHeight);

public:
	Window();
	Window(int width, int height);
	void CreateContext();

	void ToggleFullscreen();
	void SetWindowed();
	void SetFullscreen();

	void SetResolutionToWindowResolution();
	void SetResolution(int width, int height);
	vec2 GetWindowSize();

	void SwapWindow();

	~Window();
};
