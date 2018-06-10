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
		SDL_Event sdlEvent;
		while (SDL_PollEvent(&sdlEvent) != 0)
		{
			if (sdlEvent.type == SDL_QUIT)
				quit = true;

			if (sdlEvent.type == SDL_KEYDOWN)
				engine->handleKeydown(sdlEvent.key.keysym.sym);
		}

		engine->run();
	}

	delete engine;
	engine = NULL;

	return 0;
}
