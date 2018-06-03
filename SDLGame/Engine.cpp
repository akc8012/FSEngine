#include "Engine.h"
#include <iostream>
#include <string>
using namespace std;

bool Engine::init()
{
	try
	{
		window = createWindow();
	}
	catch (string msg)
	{
		cout << msg << endl;
		return false;;
	}

	SDL_UpdateWindowSurface(window);
	SDL_Delay(2000);

	return true;
}

SDL_Window* Engine::createWindow()
{
	SDL_Surface* surface = NULL;

	if (SDL_Init(SDL_INIT_VIDEO) == -1)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		throw SDL_GetError();
	}

	window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		throw SDL_GetError();
	}

	surface = SDL_GetWindowSurface(window);
	SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0x00, 0x7F, 0xFF));

	return window;
}

void Engine::quit()
{
	SDL_DestroyWindow(window);
	SDL_Quit();
}
