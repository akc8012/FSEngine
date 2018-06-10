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
			switch (sdlEvent.type)
			{
				case SDL_QUIT:
					quit = true;
				break;

				case SDL_KEYDOWN:
					engine->handleKeyboardEvent(sdlEvent.key);

					if (sdlEvent.key.keysym.sym == SDLK_ESCAPE)
						quit = true;
				break;

				case SDL_WINDOWEVENT:
					engine->handleWindowEvent(sdlEvent.window);
				break;
			}
		}

		engine->run();
	}

	delete engine;
	engine = NULL;

	return 0;
}
