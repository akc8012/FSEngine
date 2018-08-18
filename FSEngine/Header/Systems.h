#pragma once
#include "FileSystem.h"
#include "Window.h"
#include "ShaderProgram.h"
#include "Renderer.h"
#include "Timer.h"
#include "SceneManager.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <GL\glew.h>
#include <SDL_opengl.h>

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
