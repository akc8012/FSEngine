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
		screenSurface = SDL_GetWindowSurface(window);
		loadMedia();
	}
	catch (string msg)
	{
		cout << msg << endl;
		cin.get();
		return false;
	}

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
	int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
	if (!(IMG_Init(imgFlags) & imgFlags))
		throw (string)"SDL_image could not initialize! SDL_image Error: " + IMG_GetError();

	helloWorldSurface = loadSurface("Resource/Image/loaded.png");
}

SDL_Surface* Engine::loadSurface(const char* path)
{
	SDL_Surface* loadedSurface = IMG_Load(path);
	if (loadedSurface == NULL)
		throw (string)"Unable to load image! SDL_Error: " + IMG_GetError();

	SDL_Surface* finalSurface = SDL_ConvertSurface(loadedSurface, screenSurface->format, NULL);
	if (finalSurface == NULL)
		throw (string)"Unable to convert surface! SDL_Error: " + SDL_GetError();

	SDL_FreeSurface(loadedSurface);
	return finalSurface;
}

void Engine::run()
{
	SDL_BlitSurface(helloWorldSurface, NULL, screenSurface, NULL);
	SDL_UpdateWindowSurface(window);
}

void Engine::handleInput(SDL_Event& event)
{
	switch (event.key.keysym.sym)
	{
		case SDLK_UP: cout << "UP" << endl; break;
		case SDLK_DOWN: cout << "DOWN" << endl; break;
		case SDLK_LEFT: cout << "LEFT" << endl; break;
		case SDLK_RIGHT: cout << "RIGHT" << endl; break;
	}
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
