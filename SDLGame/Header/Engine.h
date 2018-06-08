#pragma once
#include "Renderer.h"
#include <SDL.h>

class Engine
{
private:
	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;

	int rectX = 30, rectY = 30;

	SDL_Window* window = NULL;
	Renderer* renderer = NULL;

	SDL_Window* createWindow();

	void loadMedia();
	void update();
	void draw();

public:
	~Engine();

	bool init();
	void run();
};
