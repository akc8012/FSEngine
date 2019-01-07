#include "../Header/Engine.h"

#pragma region Initialize
void Engine::Initialize()
{
	systems = make_unique<Systems>();
	systems->fileSystem = make_unique<FileSystem>();

	InitializeSDL();
	InitializeOpenGl();
	InitializeGlew();
	InitializeImGui();

	systems->input = make_unique<Input>();
	systems->gameTimer = make_unique<GameTimer>();
	systems->random = make_unique<Random>();

	systems->eventSystem = make_unique<EventSystem>();
	systems->eventSystem->AddListener("SurfaceSizeChanged", window.get());

	sceneManager = make_unique<SceneManager>(systems.get());
	renderer = make_unique<Renderer>(systems.get(), sceneManager->GetCurrentScene()->GetGameObjectContainer()->GetGameObject("Camera"));

	printFS("Success");
	running = true;
}

void Engine::InitializeSDL()
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
	window = make_unique<Window>(systems->fileSystem.get());

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

void Engine::InitializeGlew()
{
	glewExperimental = GL_TRUE;
	Uint32 glewError = glewInit();
	if (glewError != GLEW_OK)
		throwFS((string)"Error initializing GLEW! " + (const char*)glewGetErrorString(glewError));
}

void Engine::InitializeImGui()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls

	ImGui_ImplSDL2_InitForOpenGL(window->GetSDLWindow(), openGlContext);
	ImGui_ImplOpenGL3_Init("#version 330");

	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();
}

bool Engine::IsRunning() const
{
	return running;
}

void Engine::Stop(bool caughtException)
{
	if (!caughtException)
		systems->eventSystem->SendEvent("GameStopped");

	running = false;
}
#pragma endregion

void Engine::GameLoop()
{
	PollEvents();

	HandleKeyboardShortcuts();

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
			Stop();
			break;

		case SDL_KEYDOWN:
			HandleKeyboardEvent(sdlEvent.key);
			break;

		case SDL_WINDOWEVENT:
			HandleWindowEvent(sdlEvent.window);
			break;

		case SDL_MOUSEWHEEL:
			systems->input->SetMouseWheelScroll(sdlEvent.wheel.y);
			break;

		case SDL_MOUSEBUTTONDOWN:
			systems->input->SetMouseButtonPress(sdlEvent.button.button);
			break;

		case SDL_MOUSEBUTTONUP:
			systems->input->SetMouseButtonRelease(sdlEvent.button.button);
			break;
		}

		ImGui_ImplSDL2_ProcessEvent(&sdlEvent);
	}
}

void Engine::HandleKeyboardEvent(const SDL_KeyboardEvent& keyboardEvent)
{
	switch (keyboardEvent.keysym.sym)
	{
	case SDLK_ESCAPE:
		Stop();
		break;

	case SDLK_x:
		try
		{
			renderer->ReCompileShaders();
			printFS("Rebuilt shader program");
		}
		catch (string errorMessage)
		{
			printFS(errorMessage);
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
	case SDL_WINDOWEVENT_SHOWN:
		systems->eventSystem->SendEvent("SurfaceSizeChanged", json { window->GetSurfaceSize().x, window->GetSurfaceSize().y });
		break;

	case SDL_WINDOWEVENT_SIZE_CHANGED:
		systems->eventSystem->SendEvent("SurfaceSizeChanged", json { windowEvent.data1, windowEvent.data2 });
		break;

	case SDL_WINDOWEVENT_FOCUS_GAINED:
		if (systems->fileSystem->GetSettingsValue<bool>("LoadSettingsOnFocus"))
		{
			systems->fileSystem->LoadSettingsFile();
			SetOpenGlParameters();
		}

		systems->eventSystem->SendEvent("WindowFocusGained");
		break;

	case SDL_WINDOWEVENT_FOCUS_LOST:
		systems->eventSystem->SendEvent("WindowFocusLost");
		break;
	}
}

void Engine::HandleKeyboardShortcuts()
{
	if (systems->input->IsButtonHeld(SDL_SCANCODE_LCTRL))
	{
		if (systems->input->IsButtonPressed(SDL_SCANCODE_S))
			systems->eventSystem->SendEvent("SaveKeyPressed");

		if (systems->input->IsButtonPressed(SDL_SCANCODE_O))
			systems->eventSystem->SendEvent("LoadKeyPressed");

		if (systems->input->IsButtonPressed(SDL_SCANCODE_Z))
			systems->eventSystem->SendEvent("UndoKeyPressed");
	}
}
#pragma endregion

void Engine::Update()
{
	if (systems->fileSystem->GetSettingsValue<bool>("ContinualSettingsReload"))
		systems->fileSystem->LoadSettingsFile();

	if (window->ContinuallyReloadSurfaceSizeSetting())
		window->SetSurfaceSizeSizeFromSettingsValue();

	renderer->StartImGuiFrame(window.get());

	systems->gameTimer->Update();

	sceneManager->Update();

	systems->input->Update();
}

void Engine::Draw()
{
	renderer->StartRender(window.get());

	sceneManager->Draw(renderer.get());

	renderer->EndRender(window.get());
}

SDL_Window* Engine::GetSDLWindow() const
{
	return window->GetSDLWindow();
}

Engine::~Engine()
{
	sceneManager.reset();

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	SDL_GL_DeleteContext(openGlContext);
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}
