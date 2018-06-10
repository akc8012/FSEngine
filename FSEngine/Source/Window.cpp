#include "../Header/Window.h"
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
	SDL_SetWindowFullscreen(window, SDL_WINDOW_RESIZABLE);
	SDL_SetWindowSize(window, StartWidth, StartHeight);
}

void Window::setFullscreen()
{
	SDL_DisplayMode displayMode;
	SDL_GetCurrentDisplayMode(0, &displayMode);

	SDL_SetWindowSize(window, displayMode.w, displayMode.h);
	SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
}

Window::~Window()
{
	SDL_DestroyWindow(window);
}
