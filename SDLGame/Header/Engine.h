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

	int rectX = 30, rectY = 30;

	SDL_Window* window = NULL;
	SDL_Renderer* renderer;
	SDL_Texture* texture = NULL;

	SDL_Window* createWindow();
	SDL_Renderer* createRenderer();
	SDL_Texture* loadTexture(const char* path);

	void loadMedia();
	void update();
	void draw();

public:
	bool init();
	void handleInput(SDL_Event& event);
	void run();
	void quit();
};
