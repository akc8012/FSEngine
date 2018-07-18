#include "../Header/Engine.h"

bool Engine::IsRunning() const
{
	return running;
}

bool Engine::Init()
{
	try
	{
		fileSystem = new FileSystem();

		InitSDL();
		window = new Window(fileSystem);

		InitOpenGl();
		InitGlew();

		input = new Input();

		shaderProgram = new ShaderProgram();
		renderer = new Renderer(fileSystem, window, shaderProgram, input);

		cubeFace = new CubePrimitive(fileSystem, input, window);
		cubeBrick = new CubePrimitive(fileSystem, input, window);
		renderText = new RenderText(fileSystem, input, window);
		model = new Model("C:/Model/Arwing/arwing.dae", fileSystem, input, window);

		cubeFace->AddComponent(new TextureComponent("Resource/Image/awesomeface.png"));
		cubeBrick->AddComponent(new TextureComponent("Resource/Image/wall.png"));

		cubeFace->GetComponent<TransformComponent>()->SetPosition(vec3(4.5f, 0.2f, 0));
		cubeBrick->GetComponent<TransformComponent>()->SetPosition(vec3(6, -0.2f, 0.1f));
		cubeBrick->GetComponent<TransformComponent>()->SetScale(vec3(2, 0.8f, 2.8f));

		renderText->SetPixelScale(26);
		renderText->SetScreenAnchorPoint(RenderText::TopLeft);
		renderText->SetTextAlignment(RenderText::TopLeft);
		renderText->SetPixelPosition(vec2(5, -5));
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
		{
			fileSystem->LoadSettingsFile();
			printf("Reloaded settings file\n");
		}

		if (fileSystem->GetSettingsValue<bool>("LoadShadersOnFocus"))
		{
			shaderProgram->CompileShaders();
			printf("Rebuilt shader program\n");
		}
		break;
	}
}

void Engine::Update(float deltaTime)
{
	cubeFace->Update(deltaTime);
	cubeBrick->Update(deltaTime);

	renderText->Update(deltaTime);
	renderText->SetText(fileSystem->GetSettingsValue<string>("RenderText"));
}

void Engine::Draw(float deltaTime)
{
	renderer->StartRender(deltaTime);

	glEnable(GL_DEPTH_TEST);
	shaderProgram->SetBool("renderPerspective", true);
	renderer->RenderGameObject(cubeFace);
	renderer->RenderGameObject(cubeBrick);
	renderer->RenderModel(model);

	glDisable(GL_DEPTH_TEST);
	shaderProgram->SetBool("renderPerspective", false);
	renderer->RenderGameObject(renderText);

	renderer->EndRender();
}

Engine::~Engine()
{
	delete model;
	delete renderText;
	delete cubeFace;
	delete cubeBrick;

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
