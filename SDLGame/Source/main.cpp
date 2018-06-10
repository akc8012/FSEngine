#include "../Header/Engine.h"

void runGameLoop(Engine* engine)
{
	while (true)
	{
		SDL_Event sdlEvent;
		while (SDL_PollEvent(&sdlEvent) != 0)
		{
			switch (sdlEvent.type)
			{
				//to-do: fix console window persisting on quit
				case SDL_QUIT:
					return;
				break;

				case SDL_KEYDOWN:
					engine->handleKeyboardEvent(sdlEvent.key);

					if (sdlEvent.key.keysym.sym == SDLK_ESCAPE)
						return;
				break;

				case SDL_WINDOWEVENT:
					engine->handleWindowEvent(sdlEvent.window);
				break;
			}
		}

		engine->run();
	}
}

int main(int argc, char* args[])
{
	Engine* engine = new Engine();
	if (!engine->init())
	{
		delete engine;
		return -1;
	}

	runGameLoop(engine);

	delete engine;
	engine = NULL;

	return 0;
}
