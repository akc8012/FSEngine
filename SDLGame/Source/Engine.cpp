#include "../Header/Engine.h"
#include <iostream>
#include <string>
using namespace std;

bool Engine::init()
{
	try
	{
		if (SDL_Init(SDL_INIT_VIDEO) != 0)
			throw (string)"SDL could not initialize! SDL_Error: " + SDL_GetError();

		window = createWindow();
		loadMedia();
	}
	catch (string msg)
	{
		cout << msg << endl;
		cin.get();
		return false;
	}

	screenSurface = SDL_GetWindowSurface(window);
	return true;
}

SDL_Window* Engine::createWindow()
{
	window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == NULL)
		throw (string)"Window could not be created! SDL_Error: " + SDL_GetError();

	return window;
}

void Engine::loadMedia()
{
	helloWorldSurface = SDL_LoadBMP("Resource/Image/hello_world.bmp");
	if (helloWorldSurface == NULL)
		throw (string)"Unable to load image! SDL_Error: " + SDL_GetError();
}

void Engine::run()
{
	SDL_BlitSurface(helloWorldSurface, NULL, screenSurface, NULL);
	SDL_UpdateWindowSurface(window);
}

void Engine::quit()
{
	SDL_FreeSurface(helloWorldSurface);
	helloWorldSurface = NULL;

	SDL_DestroyWindow(window);
	window = NULL;
	screenSurface = NULL;

	SDL_Quit();
}
