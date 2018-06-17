#include "../Header/Engine.h"
#include <SDL_image.h>
#include <string>
using namespace std;

bool Engine::init()
{
	try
	{
		if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER) != 0)
			throw (string)"SDL could not initialize! SDL_Error: " + SDL_GetError();

		if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
			throw (string)"SDL_image could not initialize! SDL_image Error: " + IMG_GetError();

		window = new Window();
		renderer = new Renderer(window->get());
	}
	catch (string errorMessage)
	{
		printf("%s\n", errorMessage.c_str());
		getchar();
		return false;
	}

	printf("Success\n");
	return true;
}

void Engine::handleWindowEvent(const SDL_WindowEvent& windowEvent)
{
	if (windowEvent.event == SDL_WINDOWEVENT_SIZE_CHANGED)
	{
		int width, height;
		SDL_GetWindowSize(window->get(), &width, &height);
		window->setResolution(width, height);
	}
}

void Engine::handleKeyboardEvent(const SDL_KeyboardEvent& keyboardEvent)
{
	switch (keyboardEvent.keysym.sym)
	{
		case SDLK_x:
			try
			{
				renderer->recompileShaders();
				printf("Rebuilt shader program\n");
			}
			catch (string errorMessage)
			{
				printf("%s\n", errorMessage.c_str());
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
	delete renderer;
	delete window;

	IMG_Quit();
	SDL_Quit();
}
