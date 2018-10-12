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
	void SetSurfaceSize(const tvec2<int>& surfaceSize);

	void CreateWindow(const tvec2<int>& surfaceSize, bool fullscreen);
	tvec2<int> GetSurfaceSizeSettingsValue() const;
	tvec2<int> GetScreenResolution() const;

public:
	Window(FileSystem* fileSystem);
	~Window();

	void ToggleFullscreen();
	void SetViewportToSurfaceSize();
	void SetSurfaceSizeSizeFromSettingsValue();

	tvec2<int> GetSurfaceSize() const;
	SDL_Window* GetSDLWindow() const;

	bool ContinuallyReloadSurfaceSizeSetting() const;
	bool IsFullscreen() const;

	void SwapWindow();
};
