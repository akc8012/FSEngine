#pragma once
#include "FileSystem.h"

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
	FileSystem* fileSystem = nullptr;
	SDL_Window* window = nullptr;
	SDL_GLContext context = nullptr;

	void SetWindowed();
	void SetFullscreen();

	void CreateContext();
	void CreateWindow(tvec2<int> size, bool fullscreen);
	tvec2<int> GetResolutionSetting() const;
	tvec2<int> GetScreenResolution() const;

public:
	Window(FileSystem* fileSystem);
	Window(FileSystem* fileSystem, tvec2<int> size, bool fullscreen);

	void ToggleFullscreen();
	void SetResolutionToWindowResolution();

	void SetResolution(int width, int height);
	tvec2<int> GetWindowSize() const;

	void SwapWindow();

	~Window();
};
