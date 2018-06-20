#include "../Header/Engine.h"
#include "../Header/Timer.h"
#include <SDL_image.h>
#include <string>
using namespace std;

bool Engine::IsRunning()
{
	return running;
}

bool Engine::Init()
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

	running = true;
	return running;
}

void Engine::PollEvents()
{
	SDL_Event sdlEvent;
	while (SDL_PollEvent(&sdlEvent) != NULL)
	{
		switch (sdlEvent.type)
		{
			//to-do: fix console window persisting on quit
			case SDL_QUIT:
				running = false;
			break;

			case SDL_KEYDOWN:
				HandleKeyboardEvent(sdlEvent.key);

				if (sdlEvent.key.keysym.sym == SDLK_ESCAPE)
					running = false;
			break;

			case SDL_WINDOWEVENT:
				HandleWindowEvent(sdlEvent.window);
			break;
		}
	}
}

void Engine::HandleWindowEvent(const SDL_WindowEvent& windowEvent)
{
	switch (windowEvent.event)
	{
		case SDL_WINDOWEVENT_SIZE_CHANGED:
			int width, height;
			SDL_GetWindowSize(window->get(), &width, &height);
			window->SetResolution(width, height);
		break;
	}
}

void Engine::HandleKeyboardEvent(const SDL_KeyboardEvent& keyboardEvent)
{
	switch (keyboardEvent.keysym.sym)
	{
		case SDLK_x:
			try
			{
				renderer->RecompileShaders();
				printf("Rebuilt shader program\n");
			}
			catch (string errorMessage)
			{
				printf("%s\n", errorMessage.c_str());
			}
		break;

		case SDLK_F11:
		case SDLK_F12:
			window->ToggleFullscreen();
		break;
	}
}

void Engine::Update()
{
	//printf("%f\n", Timer::getFramesPerSecond());
}

void Engine::Draw()
{
	renderer->Render(window->get());
}

Engine::~Engine()
{
	delete renderer;
	delete window;

	IMG_Quit();
	SDL_Quit();

	running = false;
}
