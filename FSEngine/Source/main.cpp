#include "../Header/Engine.h"

int main(int argc, char* args[])
{
	Engine* engine = new Engine();
	if (!engine->init())
	{
		delete engine;
		return -1;
	}

	while (engine->isRunning())
	{
		engine->pollEvents();
		engine->update();
		engine->draw();
	}

	delete engine;
	return 0;
}
