#pragma once
#include <SDL.h>
#include <glm/glm.hpp>
using namespace glm;

class Window
{
private:
	static const int StartWidth = 800, StartHeight = 600;

	SDL_Window* window;
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
