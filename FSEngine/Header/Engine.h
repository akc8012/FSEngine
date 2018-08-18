#pragma once
#include "FileSystem.h"
#include "Window.h"
#include "ShaderProgram.h"
#include "Renderer.h"
#include "Timer.h"
#include "GameObject.h"
#include "SceneManager.h"
#include "CubePrimitive.h"
#include "RenderText.h"
#include "Model.h"
#include "PlayerShip.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <GL\glew.h>
#include <SDL_opengl.h>

#include <string>

#pragma region Systems
struct Systems
{
private:
	void InitSDL();
	void InitOpenGl();
	void InitGlew();

public:
	FileSystem* fileSystem = nullptr;
	Window* window = nullptr;
	ShaderProgram* shaderProgram = nullptr;
	Input* input = nullptr;
	Renderer* renderer = nullptr;
	SceneManager* sceneManager = nullptr;

	Systems();
	~Systems();

	void ToggleSwapInterval();
	void SetSwapInterval(int interval);
};
#pragma endregion

#pragma region Engine
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
#pragma endregion
