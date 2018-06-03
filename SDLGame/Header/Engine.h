#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

class Engine
{
private:
	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;

	SDL_Window* window = NULL;
	SDL_Surface* screenSurface = NULL;
	SDL_Surface* helloWorldSurface = NULL;

	SDL_Window* createWindow();
	void loadMedia();
	SDL_Surface* loadSurface(const char* path);

public:
	bool init();
	void handleInput(SDL_Event& event);
	void run();
	void quit();
};
