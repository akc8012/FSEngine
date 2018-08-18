#include "../Header/Engine.h"

int main(int argc, char* args[])
{
	Engine* engine = new Engine();
	try
	{
		engine->Initialize();
	}
	catch (string errorMessage)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "INIT ERROR", errorMessage.c_str(), nullptr);
	}

	while (engine->IsRunning())
	{
		try
		{
			engine->GameLoop();
		}
		catch (string errorMessage)
		{
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "GAMELOOP ERROR", errorMessage.c_str(), engine->GetSDLWindow());
			engine->Stop();
		}
	}

	delete engine;
	return 0;
}
