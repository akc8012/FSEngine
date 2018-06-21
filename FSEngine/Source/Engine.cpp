#include "../Header/Engine.h"

bool Engine::IsRunning()
{
	return running;
}

bool Engine::Init()
{
	try
	{
		InitSDL();

		window = new Window();

		InitOpenGl();
		InitGlew();

		shaderProgram = new ShaderProgram();
		renderer = new Renderer(shaderProgram);
	}
	catch (string errorMessage)
	{
		printf("%s\n", errorMessage.c_str());
		getchar();
		return false;
	}

	printf("Success\n");

	running = true;
	return running;
}

void Engine::InitSDL()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER) != 0)
		throw (string)"SDL could not initialize! SDL_Error: " + SDL_GetError();

	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
		throw (string)"SDL_image could not initialize! SDL_image Error: " + IMG_GetError();
}

void Engine::InitOpenGl()
{
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	const int VSyncOn = 0;
	if (SDL_GL_SetSwapInterval(VSyncOn) != 0)
		throw (string)"Error: Unable to set swap interval! SDL Error: " + SDL_GetError();

	glEnable(GL_DEPTH_TEST);
}

void Engine::InitGlew()
{
	glewExperimental = GL_TRUE;
	unsigned int glewError = glewInit();
	if (glewError != GLEW_OK)
		throw (string)"Error initializing GLEW! " + (const char*)glewGetErrorString(glewError);
}

void Engine::PollEvents()
{
	SDL_Event sdlEvent;
	while (SDL_PollEvent(&sdlEvent) != NULL)
	{
		switch (sdlEvent.type)
		{
			//to-do: fix console window persisting on quit
			case SDL_QUIT:
				running = false;
			break;

			case SDL_KEYDOWN:
				HandleKeyboardEvent(sdlEvent.key);

				if (sdlEvent.key.keysym.sym == SDLK_ESCAPE)
					running = false;
			break;

			case SDL_WINDOWEVENT:
				HandleWindowEvent(sdlEvent.window);
			break;
		}
	}
}

void Engine::HandleWindowEvent(const SDL_WindowEvent& windowEvent)
{
	switch (windowEvent.event)
	{
		case SDL_WINDOWEVENT_SIZE_CHANGED:
			window->SetResolutionToWindowResolution();
		break;
	}
}

void Engine::HandleKeyboardEvent(const SDL_KeyboardEvent& keyboardEvent)
{
	switch (keyboardEvent.keysym.sym)
	{
		case SDLK_x:
			try
			{
				renderer->RecompileShaders();
				printf("Rebuilt shader program\n");
			}
			catch (string errorMessage)
			{
				printf("%s\n", errorMessage.c_str());
			}
		break;

		case SDLK_F11:
		case SDLK_F12:
			window->ToggleFullscreen();
		break;
	}
}

void Engine::Update()
{
	//to-do: update timer object here, let other objects use it for delta time
}

void Engine::Draw()
{
	renderer->Render(window);
}

Engine::~Engine()
{
	delete renderer;
	delete shaderProgram;
	delete window;

	IMG_Quit();
	SDL_Quit();

	running = false;
}
