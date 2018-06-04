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
		}

		engine->run();
	}

	delete engine;
	engine = NULL;

	return 0;
}
