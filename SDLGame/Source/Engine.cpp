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

		window = createWindow();
		renderer = new Renderer(window);


		Texture* texture = new Texture("Resource/Image/wall.png");
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

SDL_Window* Engine::createWindow(int width, int height)
{
	if (window != NULL)
		SDL_DestroyWindow(window);

	const int PositionX = 1420, PositionY = 700;
	window = SDL_CreateWindow("SDL Tutorial", PositionX, PositionY, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
	if (window == NULL)
		throw (string)"Window could not be created: " + SDL_GetError();

	return window;
}

void Engine::handleKeyboardEvent(SDL_KeyboardEvent keyboardEvent)
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

		case SDLK_F11:
		case SDLK_F12:
			SDL_GetWindowFlags(window) & SDL_WINDOW_FULLSCREEN ? setWindowed() : setFullscreen();
		break;
	}
}

void Engine::setFullscreen()
{
	SDL_DisplayMode displayMode;
	SDL_GetCurrentDisplayMode(0, &displayMode);

	SDL_SetWindowSize(window, displayMode.w, displayMode.h);
	SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
}

void Engine::setWindowed()
{
	SDL_SetWindowFullscreen(window, SDL_WINDOW_RESIZABLE);
	SDL_SetWindowSize(window, WindowStartWidth, WindowStartHeight);
}

void Engine::handleWindowEvent(SDL_WindowEvent windowEvent)
{
	if (windowEvent.event == SDL_WINDOWEVENT_SIZE_CHANGED)
	{
		try
		{
			//to-do: fix memory leak
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

//to-do: fix hanging here
Engine::~Engine()
{
	SDL_DestroyWindow(window);
	window = NULL;

	delete renderer;
	renderer = NULL;

	IMG_Quit();
	SDL_Quit();
}
