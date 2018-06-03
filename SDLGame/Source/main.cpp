#include "../Header/Engine.h"

int main(int argc, char* args[])
{
	Engine* engine = new Engine();

	if (!engine->init())
	{
		delete engine;
		return -1;
	}

	bool quit = false;
	while (!quit)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event) != 0)
		{
			if (event.type == SDL_QUIT)
				quit = true;

			if (event.type == SDL_KEYDOWN)
				engine->handleInput(event);
		}

		engine->run();
	}

	engine->quit();
	delete engine;

	return 0;
}
