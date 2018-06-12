#include "../Header/Engine.h"
#include <SDL_image.h>
#include <iostream>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace std;
using namespace glm;

bool Engine::init()
{
	try
	{
		if (SDL_Init(SDL_INIT_VIDEO) != 0)
			throw (string)"SDL could not initialize! SDL_Error: " + SDL_GetError();

		if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
			throw (string)"SDL_image could not initialize! SDL_image Error: " + IMG_GetError();

		window = new Window();
		renderer = new Renderer(window->get());
	}
	catch (string errorMessage)
	{
		cout << errorMessage << endl;
		cin.get();
		return false;
	}

	cout << "Success" << endl;
	mathStuff();
	return true;
}

void Engine::mathStuff()
{
	vec4 vec(1, 0, 0, 1);
	mat4 trans = translate(mat4(1.0), vec3(1, 1, 0));
	vec = trans * vec;
	cout << vec.x << vec.y << vec.z << endl;
}

void Engine::handleWindowEvent(const SDL_WindowEvent& windowEvent)
{
	if (windowEvent.event == SDL_WINDOWEVENT_SIZE_CHANGED)
	{
		int width, height;
		SDL_GetWindowSize(window->get(), &width, &height);
		window->setResolution(width, height);
	}
}

void Engine::handleKeyboardEvent(const SDL_KeyboardEvent& keyboardEvent)
{
	switch (keyboardEvent.keysym.sym)
	{
		case SDLK_s:
			try
			{
				renderer->rebuildShaderProgram();
				cout << "Rebuilt shader program" << endl;
			}
			catch (string errorMessage)
			{
				cout << errorMessage << endl;
			}
		break;

		case SDLK_F11:
		case SDLK_F12:
			window->toggleFullscreen();
		break;
	}
}

void Engine::run()
{
	renderer->render(window->get());
}

//to-do: fix hanging here
Engine::~Engine()
{
	delete renderer;
	delete window;

	IMG_Quit();
	SDL_Quit();
}
