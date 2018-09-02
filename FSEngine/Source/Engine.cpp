#include "../Header/Engine.h"

#pragma region Initialize
void Engine::Initialize()
{
	systems = make_unique<Systems>();
	systems->fileSystem = make_unique<FileSystem>();
	systems->input = make_unique<Input>();
	systems->gameTimer = make_unique<GameTimer>();

	InitSDL();
	InitializeOpenGl();
	InitGlew();

	systems->shaderProgram = make_unique<ShaderProgram>();
	renderer = new Renderer(systems.get());
	sceneManager = new SceneManager(systems.get(), window);

	renderer->SetCamera(sceneManager->GetGameObjectContainer()->GetGameObject("Camera"));

	printf("Success\n");
	running = true;
}

void Engine::InitSDL()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER) != 0)
		throwFS((string)"SDL could not initialize! SDL_Error: " + SDL_GetError());

	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
		throwFS((string)"SDL_image could not initialize! SDL_image Error: " + IMG_GetError());

	if (TTF_Init() != 0)
		throwFS((string)"SDL_ttf could not initialize! SDL_ttf error: " + TTF_GetError());
}

void Engine::InitializeOpenGl()
{
	CreateOpenGlContext();

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	SetOpenGlParameters();
}

void Engine::CreateOpenGlContext()
{
	window = new Window(systems->fileSystem.get());

	SDL_GL_DeleteContext(openGlContext);
	openGlContext = SDL_GL_CreateContext(window->GetSDLWindow());
	if (openGlContext == nullptr)
		throwFS((string)"OpenGL context could not be created! SDL Error: " + SDL_GetError());
}

void Engine::SetOpenGlParameters()
{
	SetSwapInterval(systems->fileSystem->GetSettingsValue<int>("SwapInterval"));
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	bool polygonLineMode = systems->fileSystem->GetSettingsValue<bool>("PolygonLineMode");
	glPolygonMode(GL_FRONT_AND_BACK, polygonLineMode ? GL_LINE : GL_FILL);
}

void Engine::SetSwapInterval(int interval)
{
	if (SDL_GL_SetSwapInterval(interval) != 0)
		throwFS((string)"Unable to set swap interval! SDL Error: " + SDL_GetError());
}

void Engine::InitGlew()
{
	glewExperimental = GL_TRUE;
	Uint32 glewError = glewInit();
	if (glewError != GLEW_OK)
		throwFS((string)"Error initializing GLEW! " + (const char*)glewGetErrorString(glewError));
}

bool Engine::IsRunning() const
{
	return running;
}

void Engine::Stop()
{
	running = false;
}
#pragma endregion

void Engine::GameLoop()
{
	PollEvents();

	Update();

	Draw();
}

#pragma region Event Handling
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
			systems->shaderProgram->CompileShaders();
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

	case SDLK_c:
		system("CLS");
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

	case SDL_WINDOWEVENT_FOCUS_GAINED:
		if (systems->fileSystem->GetSettingsValue<bool>("LoadSettingsOnFocus"))
		{
			systems->fileSystem->LoadSettingsFile();
			SetOpenGlParameters();
		}

		if (systems->fileSystem->GetSettingsValue<bool>("LoadShadersOnFocus"))
			systems->shaderProgram->CompileShaders();

		sceneManager->GetGameObjectContainer()->GetGameObject("PlayerShip")->Start();
		break;
	}
}
#pragma endregion

void Engine::Update()
{
	if (systems->fileSystem->GetSettingsValue<bool>("ContinualSettingsReload"))
		systems->fileSystem->LoadSettingsFile();

	systems->gameTimer->UpdateDeltaTime();

	sceneManager->Update();

	systems->input->UpdateLastKeyboardState();
}

void Engine::Draw()
{
	renderer->StartRender();

	sceneManager->Draw(renderer);

	renderer->EndRender(window);
}

SDL_Window* Engine::GetSDLWindow() const
{
	return window->GetSDLWindow();
}

Engine::~Engine()
{
	delete sceneManager;
	delete renderer;
	delete window;

	SDL_GL_DeleteContext(openGlContext);
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();

	running = false;
}
