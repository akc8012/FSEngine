#include "../Header/Engine.h"

int main(int argc, char* args[])
{
	Engine* engine = new Engine();
	if (!engine->Init())
	{
		delete engine;
		return -1;
	}

	while (engine->IsRunning())
	{
		engine->PollEvents();
		engine->Update();
		engine->Draw();
	}

	delete engine;
	return 0;
}
