#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include "Renderer.h"

class Engine
{
private:
	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;

	int rectX = 30, rectY = 30;

	SDL_Window* window = NULL;
	SDL_Texture* texture = NULL;
	Renderer* renderer = NULL;

	SDL_Window* createWindow();
	//SDL_Texture* loadTexture(const char* path);

	void loadMedia();
	void update();
	void draw();

public:
	~Engine();

	bool init();
	void run();
};
