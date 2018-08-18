#pragma once
#include "Systems.h"
#include "CubePrimitive.h"
#include "RenderText.h"
#include "Model.h"
#include "PlayerShip.h"

#include <string>
using std::string;

class Engine
{
private:
	Systems* systems = nullptr;
	bool running = false;
	float lastFrameTime = 0.0f;

	void AddGameObjects();

	float CalculateDeltaTime();
	void PollEvents();
	void Update(float deltaTime);
	void Draw(float deltaTime);

	void HandleKeyboardEvent(const SDL_KeyboardEvent& keyboardEvent);
	void HandleWindowEvent(const SDL_WindowEvent& windowEvent);

public:
	~Engine();

	bool IsRunning() const;
	void Initialize();

	void GameLoop();
	void Stop();

	SDL_Window* GetWindow() const;
};
