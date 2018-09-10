#include "../Header/Engine.h"

void HandleException(const string& header, const string& message, SDL_Window* sdlWindow = nullptr)
{
	printFS(message);
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, header.c_str(), message.c_str(), sdlWindow);
}

int main(int argc, char* args[])
{
	unique_ptr<Engine> engine = make_unique<Engine>();
	try
	{
		engine->Initialize();
	}
	catch (const std::exception& exception)
	{
		HandleException("INITIALIZE ERROR", exception.what());
	}

	while (engine->IsRunning())
	{
		try
		{
			engine->GameLoop();
		}
		catch (const std::exception& exception)
		{
			HandleException("GAMELOOP ERROR", exception.what(), engine->GetSDLWindow());
			engine->Stop();
		}
	}

	return 0;
}
