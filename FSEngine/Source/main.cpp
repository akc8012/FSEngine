#include "../Header/Engine.h"

int main(int argc, char* args[])
{
	Engine* engine = new Engine();
	try
	{
		engine->Init();
	}
	catch (string errorMessage)
	{
		printf("%s\n", errorMessage.c_str());
		getchar();
	}

	while (engine->IsRunning())
	{
		try
		{
			engine->GameLoop();
		}
		catch (string errorMessage)
		{
			printf("%s\n", errorMessage.c_str());
			getchar();
		}
	}

	delete engine;
	return 0;
}
