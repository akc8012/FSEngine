#include "../Header/Engine.h"

int main(int argc, char* args[])
{
	Engine* engine = new Engine();

	if (!engine->init())
	{
		delete engine;
		return -1;
	}

	engine->run();
	engine->quit();

	delete engine;
	return 0;
}
