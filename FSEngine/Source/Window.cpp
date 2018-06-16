#include "../Header/Window.h"
#include <GL\glew.h>
#include <SDL_opengl.h>
#include <GL\GLU.h>
#include <string>
using namespace std;

Window::Window()
{
	window = createWindow();
}

Window::Window(int width, int height)
{
	window = createWindow(width, height);
}

SDL_Window* Window::get()
{
	return window;
}

SDL_Window* Window::createWindow(int width, int height)
{
	if (window != NULL)
		SDL_DestroyWindow(window);

	window = SDL_CreateWindow("FSEngine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
	if (window == NULL)
		throw (string)"Window could not be created: " + SDL_GetError();

	return window;
}

void Window::toggleFullscreen()
{
	SDL_GetWindowFlags(window) & SDL_WINDOW_FULLSCREEN ? setWindowed() : setFullscreen();
}

void Window::setWindowed()
{
	SDL_SetWindowSize(window, StartWidth, StartHeight);
	SDL_SetWindowFullscreen(window, SDL_WINDOW_RESIZABLE);
}

void Window::setFullscreen()
{
	SDL_DisplayMode displayMode;
	SDL_GetCurrentDisplayMode(0, &displayMode);

	SDL_SetWindowSize(window, displayMode.w, displayMode.h);
	SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
}

void Window::setResolution(int width, int height)
{
	const int PositionX = 0, PositionY = PositionX;
	glViewport(PositionX, PositionY, width, height);
}

Window::~Window()
{
	SDL_DestroyWindow(window);
}
