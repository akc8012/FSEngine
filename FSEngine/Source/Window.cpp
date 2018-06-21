#include "../Header/Window.h"
#include <GL\glew.h>
#include <SDL_opengl.h>
#include <GL\GLU.h>
#include <string>
using namespace std;

Window::Window()
{
	CreateWindow();
	CreateContext();
}

Window::Window(int width, int height)
{
	CreateWindow(width, height);
	CreateContext();
}

void Window::CreateWindow(int width, int height)
{
	if (window != NULL)
		SDL_DestroyWindow(window);

	window = SDL_CreateWindow("FSEngine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
	if (window == NULL)
		throw (string)"Window could not be created: " + SDL_GetError();
}

void Window::CreateContext()
{
	SDL_GL_DeleteContext(context);
	context = SDL_GL_CreateContext(window);
	if (context == NULL)
		throw (string)"OpenGL context could not be created! SDL Error: " + SDL_GetError();
}

void Window::ToggleFullscreen()
{
	SDL_GetWindowFlags(window) & SDL_WINDOW_FULLSCREEN ? SetWindowed() : SetFullscreen();
}

void Window::SetWindowed()
{
	SDL_SetWindowSize(window, StartWidth, StartHeight);
	SDL_SetWindowFullscreen(window, SDL_WINDOW_RESIZABLE);
}

void Window::SetFullscreen()
{
	SDL_DisplayMode displayMode;
	SDL_GetCurrentDisplayMode(0, &displayMode);

	SDL_SetWindowSize(window, displayMode.w, displayMode.h);
	SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
}

void Window::SetResolutionToWindowResolution()
{
	int width, height;
	SDL_GetWindowSize(window, &width, &height);
	SetResolution(width, height);
}

void Window::SetResolution(int width, int height)
{
	const int PositionX = 0, PositionY = PositionX;
	glViewport(PositionX, PositionY, width, height);
}

vec2 Window::GetWindowSize()
{
	int width, height;
	SDL_GetWindowSize(window, &width, &height);
	return vec2(width, height);
}

void Window::SwapWindow()
{
	SDL_GL_SwapWindow(window);
}

Window::~Window()
{
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
}
