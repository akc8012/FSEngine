#include "../Header/Engine.h"

#pragma region Systems
Systems::Systems()
{
	fileSystem = new FileSystem();

	InitSDL();
	window = new Window(fileSystem);

	InitOpenGl();
	InitGlew();

	input = new Input();

	shaderProgram = new ShaderProgram();
	renderer = new Renderer(fileSystem, window, shaderProgram);

	sceneManager = new SceneManager();
}

void Systems::InitSDL()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER) != 0)
		throw (string)"SDL could not initialize! SDL_Error: " + SDL_GetError();

	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
		throw (string)"SDL_image could not initialize! SDL_image Error: " + IMG_GetError();

	if (TTF_Init() != 0)
		throw (string)"SDL_ttf could not initialize! SDL_ttf error: " + TTF_GetError();
}

void Systems::InitOpenGl()
{
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	SetSwapInterval(fileSystem->GetSettingsValue<int>("SwapInterval"));
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Systems::ToggleSwapInterval()
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

void Systems::SetSwapInterval(int interval)
{
	if (SDL_GL_SetSwapInterval(interval) != 0)
		throw (string)"Unable to set swap interval! SDL Error: " + SDL_GetError();
}

void Systems::InitGlew()
{
	glewExperimental = GL_TRUE;
	Uint32 glewError = glewInit();
	if (glewError != GLEW_OK)
		throw (string)"Error initializing GLEW! " + (const char*)glewGetErrorString(glewError);
}

Systems::~Systems()
{
	delete sceneManager;
	delete renderer;
	delete input;
	delete shaderProgram;
	delete window;
	delete fileSystem;

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}
#pragma endregion

#pragma region Initialize
void Engine::Initialize()
{
	systems = new Systems();
	AddGameObjects();
	systems->sceneManager->Initialize(systems->fileSystem, systems->input, systems->window);

	printf("Success\n");
	running = true;
}

void Engine::AddGameObjects()
{
	GameObject* memeFaceCube = systems->sceneManager->GetGameObjectContainer()->AddGameObject("MemeFaceCube", new CubePrimitive());
	memeFaceCube->AddComponent(new TextureComponent("Resource/Image/awesomeface.png"));
	memeFaceCube->GetComponent<TransformComponent>()->SetPosition(vec3(4.5f, 0.2f, 0));

	GameObject* greenCube = systems->sceneManager->GetGameObjectContainer()->AddGameObject("GreenCube", new CubePrimitive());
	greenCube->AddComponent(new ShadingComponent(vec3(0.1, 0.6, 0.3)));
	greenCube->GetComponent<TransformComponent>()->SetPosition(vec3(6, -0.2f, 0.1f));
	greenCube->GetComponent<TransformComponent>()->SetScale(vec3(2, 0.8f, 2.8f));

	systems->sceneManager->GetGameObjectContainer()->AddGameObject("1", new CubePrimitive())->GetComponent<TransformComponent>()->SetPosition(vec3(0, 1, 3));
	systems->sceneManager->GetGameObjectContainer()->AddGameObject("2", new CubePrimitive())->GetComponent<TransformComponent>()->SetPosition(vec3(1, -1, -1));
	systems->sceneManager->GetGameObjectContainer()->AddGameObject("3", new CubePrimitive())->GetComponent<TransformComponent>()->SetPosition(vec3(-0.8f, 0, -2));
	systems->sceneManager->GetGameObjectContainer()->AddGameObject("4", new CubePrimitive())->GetComponent<TransformComponent>()->SetPosition(vec3(-2, -1, 0));

	systems->sceneManager->GetGameObjectContainer()->AddGameObject("PlayerShip", new PlayerShip());

	RenderText* debugText = dynamic_cast<RenderText*>(systems->sceneManager->GetGameObjectContainer()->AddGameObject("DebugText", new RenderText()));
	debugText->SetLateRefresh(true);
	debugText->SetPixelScale(26);
	debugText->SetScreenAnchorPoint(RenderText::TopLeft);
	debugText->SetTextAlignment(RenderText::TopLeft);
	debugText->SetPixelPosition(vec2(5, -5));

	GameObject* camera = systems->sceneManager->GetGameObjectContainer()->AddGameObject("Camera", new Camera());
	camera->SetLateRefresh(true);
	systems->renderer->SetCamera(camera);
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
	float deltaTime = CalculateDeltaTime();

	PollEvents();
	Update(deltaTime);
	Draw(deltaTime);
}

float Engine::CalculateDeltaTime()
{
	float currentFrameTime = Timer::GetSeconds();
	float deltaTime = currentFrameTime - lastFrameTime;
	lastFrameTime = currentFrameTime;

	return deltaTime;
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
		systems->window->ToggleFullscreen();
		break;

	case SDLK_f:
		systems->ToggleSwapInterval();
		printf("Set swap interval to: %i\n", SDL_GL_GetSwapInterval());
		break;

	case SDLK_k:
		systems->fileSystem->LoadSettingsFile();
		printf("Reloaded settings file\n");
		break;

	case SDLK_c:
		system("CLS");
		break;
	}
}

void Engine::HandleWindowEvent(const SDL_WindowEvent& windowEvent)
{
	switch (windowEvent.event)
	{
	case SDL_WINDOWEVENT_SIZE_CHANGED:
		systems->window->SetResolutionToWindowResolution();
		break;

	case SDL_WINDOWEVENT_FOCUS_GAINED:
		if (systems->fileSystem->GetSettingsValue<bool>("LoadSettingsOnFocus"))
			systems->fileSystem->LoadSettingsFile();

		if (systems->fileSystem->GetSettingsValue<bool>("LoadShadersOnFocus"))
			systems->shaderProgram->CompileShaders();

		systems->sceneManager->GetGameObjectContainer()->GetGameObject("PlayerShip")->Start();
		break;
	}
}
#pragma endregion

void Engine::Update(float deltaTime)
{
	systems->sceneManager->Update(deltaTime);

	if (Timer::GetSeconds() > 3 && systems->sceneManager->GetGameObjectContainer()->TryGetGameObject("SpawnCube") == nullptr)
		systems->sceneManager->GetGameObjectContainer()->AddGameObject("SpawnCube", new CubePrimitive());
}

void Engine::Draw(float deltaTime)
{
	systems->renderer->StartRender(deltaTime);
	systems->sceneManager->Draw(systems->renderer);
	systems->renderer->EndRender();
}

SDL_Window* Engine::GetWindow() const
{
	return systems->window->GetWindow();
}

Engine::~Engine()
{
	delete systems;
	running = false;
}
