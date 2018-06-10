#pragma once
#include <SDL.h>

class Window
{
private:
	static const int StartWidth = 480, StartHeight = 320;
	SDL_Window* window;

	SDL_Window* createWindow(int width = StartWidth, int height = StartHeight);

public:
	Window();
	Window(int width, int height);

	SDL_Window* get();

	void toggleFullscreen();
	void setWindowed();
	void setFullscreen();
	void setResolution(int width, int height);

	~Window();
};
