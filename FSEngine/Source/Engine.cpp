#include "../Header/Engine.h"

bool Engine::IsRunning() const
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
		renderer = new Renderer(window, shaderProgram);

		faceTexture = new Texture("awesomeface.png");
		crateTexture = new Texture("wall.png");

		rotatingCrate = new RotatingCrate(faceTexture, vec3(0.5f, 0.2f, 0));
		rotatingCrate2 = new RotatingCrate(crateTexture, vec3(-0.5f, -0.2f, 0.1f));
		textQuad = new TextQuad();

		rotatingCrate2->GetTransformComponent()->SetScale(vec3(2, 0.8f, 2.8f));


		printf("%i\n", FileSystem::GetSettingValue("number").get<int>());
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

	if (TTF_Init() != 0)
		throw (string)"SDL_ttf could not initialize! SDL_ttf error: " + TTF_GetError();
}

void Engine::InitOpenGl()
{
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	const int AdaptiveVsync = -1;
	SetSwapInterval(AdaptiveVsync);

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Engine::SetSwapInterval(int interval)
{
	if (SDL_GL_SetSwapInterval(interval) != 0)
		throw (string)"Error: Unable to set swap interval! SDL Error: " + SDL_GetError();
}

void Engine::InitGlew()
{
	glewExperimental = GL_TRUE;
	Uint32 glewError = glewInit();
	if (glewError != GLEW_OK)
		throw (string)"Error initializing GLEW! " + (const char*)glewGetErrorString(glewError);
}

void Engine::GameLoop()
{
	Uint32 deltaTime = CalculateDeltaTime();

	PollEvents();
	Update(deltaTime);
	Draw(deltaTime);
}

Uint32 Engine::CalculateDeltaTime()
{
	Uint32 currentFrameStamp = SDL_GetTicks();
	Uint32 deltaTime = currentFrameStamp - lastFrameStamp;
	lastFrameStamp = currentFrameStamp;

	return deltaTime;
}

void Engine::PollEvents()
{
	SDL_Event sdlEvent;
	while (SDL_PollEvent(&sdlEvent) != NULL)
	{
		switch (sdlEvent.type)
		{
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

	case SDLK_f:
		ToggleSwapInterval();
		printf("Set swap interval to: %i\n", SDL_GL_GetSwapInterval());
		break;
	}
}

void Engine::ToggleSwapInterval()
{
	enum SwapIntervals { AdaptiveVsync = -1, VsyncOff, VsyncOn };
	int currentSwapInterval = SDL_GL_GetSwapInterval();
	int targetSwapInterval;

	switch (currentSwapInterval)
	{
	case AdaptiveVsync:
		targetSwapInterval = VsyncOff;
		break;

	case VsyncOff:
		targetSwapInterval = VsyncOn;
		break;

	case VsyncOn:
		targetSwapInterval = AdaptiveVsync;
		break;
	}

	SetSwapInterval(targetSwapInterval);
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

void Engine::Update(Uint32 deltaTime)
{
	rotatingCrate->Update(deltaTime);
	rotatingCrate2->Update(deltaTime);
}

void Engine::Draw(Uint32 deltaTime)
{
	renderer->StartRender(deltaTime);

	renderer->RenderGameObject(rotatingCrate);
	renderer->RenderGameObject(rotatingCrate2);
	renderer->RenderGameObject(textQuad);

	renderer->EndRender();
}

Engine::~Engine()
{
	delete textQuad;
	delete rotatingCrate;
	delete rotatingCrate2;

	delete faceTexture;
	delete crateTexture;

	delete renderer;
	delete shaderProgram;
	delete window;

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();

	running = false;
}
