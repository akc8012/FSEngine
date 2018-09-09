#pragma once
#include "FileSystem.h"

#include <SDL.h>
#include <GL\glew.h>
#include <SDL_opengl.h>

#include <glm\glm.hpp>
using glm::tvec2;

#include <string>
using std::string;

class Window
{
private:
	FileSystem* fileSystem = nullptr;
	SDL_Window* sdlWindow = nullptr;

	void SetWindowed();
	void SetFullscreen();
	void SetWindowSize(const tvec2<int>& windowSize);

	void CreateWindow(const tvec2<int>& windowSize, bool fullscreen);
	tvec2<int> GetWindowSizeSettingsValue() const;
	tvec2<int> GetScreenResolution() const;

public:
	Window(FileSystem* fileSystem);
	~Window();

	void ToggleFullscreen();
	void SetResolutionToWindowSize();
	void SetWindowSizeFromSettingsValue();

	tvec2<int> GetWindowSize() const;
	SDL_Window* GetSDLWindow() const;

	bool ContinuallyReloadWindowSizeSetting() const;
	bool IsFullscreen() const;

	void SwapWindow();
};
