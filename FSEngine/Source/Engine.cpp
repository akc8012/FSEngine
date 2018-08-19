#include "../Header/Engine.h"

#pragma region Initialize
void Engine::Initialize()
{
	systems = new Systems();

	InitSDL();
	InitOpenGl();
	InitGlew();

	shaderProgram = new ShaderProgram();
	renderer = new Renderer(systems->fileSystem, window, shaderProgram);

	sceneManager = new SceneManager(systems);
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
	CreateOpenGlContext();

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	SetSwapInterval(systems->fileSystem->GetSettingsValue<int>("SwapInterval"));
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Engine::CreateOpenGlContext()
{
	window = new Window(systems->fileSystem);

	SDL_GL_DeleteContext(openGlContext);
	openGlContext = SDL_GL_CreateContext(window->GetSDLWindow());
	if (openGlContext == nullptr)
		throw (string)"OpenGL context could not be created! SDL Error: " + SDL_GetError();
}

void Engine::SetSwapInterval(int interval)
{
	if (SDL_GL_SetSwapInterval(interval) != 0)
		throw (string)"Unable to set swap interval! SDL Error: " + SDL_GetError();
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
	//GameObject* memeFaceCube = sceneManager->GetGameObjectContainer()->AddGameObject("MemeFaceCube", new CubePrimitive(new TextureComponent("Resource/Image/awesomeface.png")));
	//memeFaceCube->GetComponent<TransformComponent>()->SetPosition(4.5f, 0.2f, 0);

	GameObject* greenCube = sceneManager->GetGameObjectContainer()->AddGameObject("GreenCube", new CubePrimitive(new ShadingComponent(0.1f, 0.6f, 0.3f)));
	greenCube->GetComponent<TransformComponent>()->SetPosition(0, -0.2f, 0.1f);
	greenCube->GetComponent<TransformComponent>()->SetScale(2, 0.8f, 2.8f);

	//sceneManager->GetGameObjectContainer()->AddGameObject("1", new CubePrimitive(new ShadingComponent(1, 1, 1)))->GetComponent<TransformComponent>()->SetPosition(0, 1, 3);
	//sceneManager->GetGameObjectContainer()->AddGameObject("2", new CubePrimitive(new ShadingComponent(1, 1, 1)))->GetComponent<TransformComponent>()->SetPosition(1, -1, -1);
	//sceneManager->GetGameObjectContainer()->AddGameObject("3", new CubePrimitive(new ShadingComponent(1, 1, 1)))->GetComponent<TransformComponent>()->SetPosition(-0.8f, 0, -2);
	//sceneManager->GetGameObjectContainer()->AddGameObject("4", new CubePrimitive(new ShadingComponent(1, 1, 1)))->GetComponent<TransformComponent>()->SetPosition(-2, -1, 0);

	//RenderText* debugText = dynamic_cast<RenderText*>(sceneManager->GetGameObjectContainer()->AddGameObject("DebugText", new RenderText()));
	//debugText->SetWindow(window);
	//debugText->SetLateRefresh(true);
	//debugText->SetPixelScale(26);
	//debugText->SetScreenAnchorPoint(RenderText::TopLeft);
	//debugText->SetTextAlignment(RenderText::TopLeft);
	//debugText->SetPixelPosition(vec2(5, -5));

	Camera* camera = dynamic_cast<Camera*>(sceneManager->GetGameObjectContainer()->AddGameObject("Camera", new Camera()));
	camera->SetWindow(window);
	camera->SetLateRefresh(true);
	renderer->SetCamera(sceneManager->GetGameObjectContainer()->GetGameObject("Camera"));

	//sceneManager->GetGameObjectContainer()->AddGameObject("PlayerShip", new PlayerShip());
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
		systems->fileSystem->LoadSettingsFile();
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
		if (systems->fileSystem->GetSettingsValue<bool>("LoadSettingsOnFocus"))
			systems->fileSystem->LoadSettingsFile();

		if (systems->fileSystem->GetSettingsValue<bool>("LoadShadersOnFocus"))
			shaderProgram->CompileShaders();

		//sceneManager->GetGameObjectContainer()->GetGameObject("PlayerShip")->Start();
		break;
	}
}
#pragma endregion

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

SDL_Window* Engine::GetSDLWindow() const
{
	return window->GetSDLWindow();
}

Engine::~Engine()
{
	delete sceneManager;
	delete renderer;
	delete shaderProgram;
	delete window;
	delete systems;

	SDL_GL_DeleteContext(openGlContext);
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();

	running = false;
}
