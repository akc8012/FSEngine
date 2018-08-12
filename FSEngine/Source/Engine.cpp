#include "../Header/Engine.h"

bool Engine::IsRunning() const
{
	return running;
}

void Engine::Init()
{
	fileSystem = new FileSystem();

	InitSDL();
	window = new Window(fileSystem);

	InitOpenGl();
	InitGlew();

	input = new Input();

	shaderProgram = new ShaderProgram();
	renderer = new Renderer(fileSystem, window, shaderProgram);

	sceneManager = new SceneManager(fileSystem, input, window);
	AddGameObjects();

	printf("Success\n");
	running = true;
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

	SetSwapInterval(fileSystem->GetSettingsValue<int>("SwapInterval"));
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

void Engine::AddGameObjects()
{
	GameObject* memeFaceCube = sceneManager->AddGameObject("MemeFaceCube", new CubePrimitive());
	memeFaceCube->AddComponent(new TextureComponent("Resource/Image/awesomeface.png"));
	memeFaceCube->GetComponent<TransformComponent>()->SetPosition(vec3(4.5f, 0.2f, 0));

	GameObject* greenCube = sceneManager->AddGameObject("GreenCube", new CubePrimitive());
	greenCube->AddComponent(new ShadingComponent(vec3(0.1, 0.6, 0.3)));
	greenCube->GetComponent<TransformComponent>()->SetPosition(vec3(6, -0.2f, 0.1f));
	greenCube->GetComponent<TransformComponent>()->SetScale(vec3(2, 0.8f, 2.8f));

	GameObject* shipModel = sceneManager->AddGameObject("ShipModel", new Model("C:/Model/Arwing/arwing.dae"));
	shipModel->GetComponent<TransformComponent>()->SetScale(vec3(0.025f, 0.025f, 0.025f));

	RenderText* debugText = dynamic_cast<RenderText*>(sceneManager->AddGameObject("DebugText", new RenderText()));
	debugText->SetPixelScale(26);
	debugText->SetScreenAnchorPoint(RenderText::TopLeft);
	debugText->SetTextAlignment(RenderText::TopLeft);
	debugText->SetPixelPosition(vec2(5, -5));

	GameObject* camera = sceneManager->AddGameObject("Camera", new Camera());
	renderer->SetCamera(camera);
}

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
			shaderProgram->CompileShaders();
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

	case SDLK_k:
		fileSystem->LoadSettingsFile();
		printf("Reloaded settings file\n");
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
		if (fileSystem->GetSettingsValue<bool>("LoadSettingsOnFocus"))
			fileSystem->LoadSettingsFile();

		if (fileSystem->GetSettingsValue<bool>("LoadShadersOnFocus"))
			shaderProgram->CompileShaders();

		break;
	}
}

void Engine::Update(float deltaTime)
{
	sceneManager->Update(deltaTime);
}

void Engine::Draw(float deltaTime)
{
	renderer->StartRender(deltaTime);
	sceneManager->Draw(renderer);
	renderer->EndRender();
}

void Engine::Stop()
{
	running = false;
}

Engine::~Engine()
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

	running = false;
}
