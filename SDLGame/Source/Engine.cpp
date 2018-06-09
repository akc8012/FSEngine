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
	catch (string errorMessage)
	{
		cout << errorMessage << endl;
		cin.get();
		return false;
	}

	cout << "Success" << endl;
	return true;
}

SDL_Window* Engine::createWindow()
{
	if (window != NULL)
		SDL_DestroyWindow(window);

	int ScreenWidth = 480;
	int ScreenHeight = 320;
	window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ScreenWidth, ScreenHeight, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
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


	switch (keycode)
	{
		case SDLK_s:
		{
			try
			{
				renderer->rebuildShaderProgram();
				cout << "Rebuilt shader program" << endl;
			}
			catch (string errorMessage)
			{
				cout << errorMessage << endl;
			}
			break;
		}
		case SDLK_w:
		{
			try
			{
				window = createWindow();
				renderer = new Renderer(window);
				cout << "Recreated window" << endl;
			}
			catch (string errorMessage)
			{
				cout << errorMessage << endl;
			}
			break;
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
