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

	SDL_Window* window = nullptr;
	SDL_GLContext context = nullptr;

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
	vec2 GetWindowSize() const;

	void SwapWindow();

	~Window();
};
