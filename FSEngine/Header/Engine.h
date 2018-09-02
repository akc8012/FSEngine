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
	SDL_GLContext openGlContext = nullptr;

	unique_ptr<Systems> systems;
	unique_ptr<Window> window;
	unique_ptr<Renderer> renderer;
	unique_ptr<SceneManager> sceneManager;

	void InitSDL();

	void InitializeOpenGl();
	void CreateOpenGlContext();
	void SetOpenGlParameters();

	void InitGlew();

	void ToggleSwapInterval();
	void SetSwapInterval(int interval);

	void PollEvents();
	void Update();
	void Draw();

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
