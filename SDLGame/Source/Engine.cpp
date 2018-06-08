#include "../Header/Engine.h"
#include <iostream>
#include <string>
#include <SDL_image.h>
using namespace std;

bool Engine::init()
{
	try
	{
		if (SDL_Init(SDL_INIT_VIDEO) != 0)
			throw (string)"SDL could not initialize! SDL_Error: " + SDL_GetError();

		window = createWindow();
		renderer = new Renderer(window);

		loadMedia();
	}
	catch (string msg)
	{
		cout << msg << endl;
		cin.get();
		return false;
	}

	cout << "Success" << endl;
	return true;
}

SDL_Window* Engine::createWindow()
{
	window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
	if (window == NULL)
		throw (string)"Window could not be created! SDL_Error: " + SDL_GetError();

	return window;
}

void Engine::loadMedia()
{
	int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
	if (!(IMG_Init(imgFlags) & imgFlags))
		throw (string)"SDL_image could not initialize! SDL_image Error: " + IMG_GetError();

	//texture = loadTexture("Resource/Image/loaded.png");
}

void Engine::run()
{
	update();
	draw();
}

void Engine::update()
{
	const int SPEED = 3;
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
	if (currentKeyStates[SDL_SCANCODE_UP])
		rectY -= SPEED;
	if (currentKeyStates[SDL_SCANCODE_DOWN])
		rectY += SPEED;
	if (currentKeyStates[SDL_SCANCODE_LEFT])
		rectX -= SPEED;
	if (currentKeyStates[SDL_SCANCODE_RIGHT])
		rectX += SPEED;
}

void Engine::draw()
{
	renderer->render(window);
}

Engine::~Engine()
{
	SDL_DestroyTexture(texture);
	texture = NULL;

	SDL_DestroyWindow(window);
	window = NULL;

	delete renderer;
	renderer = NULL;

	IMG_Quit();
	SDL_Quit();
}
