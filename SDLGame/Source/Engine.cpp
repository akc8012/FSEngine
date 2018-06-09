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
		renderer = new Renderer(window);
	}
	catch (string message)
	{
		cout << message << endl;
		cin.get();
		return false;
	}

	cout << "Success" << endl;
	return true;
}

SDL_Window* Engine::createWindow()
{
	window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
	if (window == NULL)
		throw (string)"Window could not be created! SDL_Error: " + SDL_GetError();

	return window;
}

void Engine::handleKeydown(SDL_Keycode keycode)
{
	if (keycode == SDLK_s)
	{
		try
		{
			renderer->rebuildShaderProgram();
		}
		catch (string message)
		{
			cout << message << endl;
		}
	}
}

void Engine::run()
{
	update();
	renderer->render(window);
}

void Engine::update()
{

}

Engine::~Engine()
{
	SDL_DestroyWindow(window);
	window = NULL;

	delete renderer;
	renderer = NULL;

	SDL_Quit();
}
