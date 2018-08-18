#include "../Header/Engine.h"

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
