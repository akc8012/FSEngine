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

	int PositionX = 1420, PositionY = 700, ScreenWidth = 480, ScreenHeight = 320;
	window = SDL_CreateWindow("SDL Tutorial", PositionX, PositionY, ScreenWidth, ScreenHeight, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
	if (window == NULL)
		throw (string)"Window could not be created: " + SDL_GetError();

	return window;
}

void Engine::handleKeyboardEvent(SDL_KeyboardEvent keyboardEvent)
{
	switch (keyboardEvent.keysym.sym)
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
				delete renderer;
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

void Engine::handleWindowEvent(SDL_WindowEvent windowEvent)
{
	if (windowEvent.event == SDL_WINDOWEVENT_SIZE_CHANGED)
	{
		try
		{
			delete renderer;
			renderer = new Renderer(window);
		}
		catch (string errorMessage)
		{
			cout << errorMessage << endl;
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
