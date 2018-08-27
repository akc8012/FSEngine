#pragma once
#include "Systems.h"
#include "Window.h"
#include "Renderer.h"
#include "Timer.h"
#include "GameObject.h"
#include "SceneManager.h"
#include "FSException.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <GL\glew.h>
#include <SDL_opengl.h>

class Engine
{
private:
	bool running = false;
	float lastFrameTime = 0.0f;

	SDL_GLContext openGlContext = nullptr;
	Systems* systems = nullptr;
	Window* window = nullptr;
	Renderer* renderer = nullptr;
	SceneManager* sceneManager = nullptr;

	void InitSDL();

	void InitializeOpenGl();
	void CreateOpenGlContext();
	void SetOpenGlParameters();

	void InitGlew();

	void ToggleSwapInterval();
	void SetSwapInterval(int interval);

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

	SDL_Window* GetSDLWindow() const;
};
