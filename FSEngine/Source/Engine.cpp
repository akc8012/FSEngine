#include "../Header/Engine.h"
#include <SDL_image.h>
#include <iostream>
#include <string>
using namespace std;

bool Engine::init()
{
	try
	{
		if (SDL_Init(SDL_INIT_VIDEO) != 0)
			throw (string)"SDL could not initialize! SDL_Error: " + SDL_GetError();

		if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
			throw (string)"SDL_image could not initialize! SDL_image Error: " + IMG_GetError();

		window = new Window();
		renderer = new Renderer(window->get());
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

void Engine::handleWindowEvent(const SDL_WindowEvent& windowEvent)
{
	if (windowEvent.event == SDL_WINDOWEVENT_SIZE_CHANGED)
	{
		try
		{
			//to-do: fix memory leak
			delete renderer;
			renderer = new Renderer(window->get());
		}
		catch (string errorMessage)
		{
			cout << errorMessage << endl;
		}
	}
}

void Engine::handleKeyboardEvent(const SDL_KeyboardEvent& keyboardEvent)
{
	switch (keyboardEvent.keysym.sym)
	{
		case SDLK_s:
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

		case SDLK_w:
			try
			{
				delete window;
				window = new Window();

				delete renderer;
				renderer = new Renderer(window->get());
				cout << "Recreated window" << endl;
			}
			catch (string errorMessage)
			{
				cout << errorMessage << endl;
			}
		break;

		case SDLK_F11:
		case SDLK_F12:
			window->toggleFullscreen();
		break;
	}
}

void Engine::run()
{
	renderer->render(window->get());
}

//to-do: fix hanging here
Engine::~Engine()
{
	delete window;
	delete renderer;

	IMG_Quit();
	SDL_Quit();
}
