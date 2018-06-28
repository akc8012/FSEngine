#pragma once
#include "Window.h"
#include "ShaderProgram.h"
#include "Renderer.h"
#include "Timer.h"
#include "GameObject.h"
#include "RotatingCrate.h"
#include "TextQuad.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <GL\glew.h>
#include <SDL_opengl.h>

#include <string>
using namespace std;

class Engine
{
private:
	bool running = false;
	Uint32 lastFrameStamp = 0;

	Window* window = nullptr;
	ShaderProgram* shaderProgram = nullptr;
	Renderer* renderer = nullptr;

	Texture* crateTexture = nullptr;
	Texture* faceTexture = nullptr;
	GameObject* rotatingCrate = nullptr;
	GameObject* rotatingCrate2 = nullptr;
	GameObject* textQuad = nullptr;

	void InitSDL();
	void InitOpenGl();
	void InitGlew();

	void ToggleSwapInterval();
	void SetSwapInterval(int interval);

	Uint32 CalculateDeltaTime();
	void PollEvents();
	void Update(Uint32 deltaTime);
	void Draw(Uint32 deltaTime);

	void HandleKeyboardEvent(const SDL_KeyboardEvent& keyboardEvent);
	void HandleWindowEvent(const SDL_WindowEvent& windowEvent);

public:
	~Engine();

	bool IsRunning() const;
	bool Init();

	void GameLoop();
};
