#pragma once
#include <SDL.h>

class Window
{
private:
	static const int StartWidth = 800, StartHeight = 600;
	
	SDL_Window* window;

	SDL_Window* createWindow(int width = StartWidth, int height = StartHeight);

public:
	Window();
	Window(int width, int height);

	SDL_Window* get();

	void ToggleFullscreen();
	void SetWindowed();
	void SetFullscreen();
	void SetResolution(int width, int height);

	~Window();
};
