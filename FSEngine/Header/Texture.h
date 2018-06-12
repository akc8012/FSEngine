#pragma once
#include <SDL_image.h>
#include <SDL.h>

class Texture
{
private:
	unsigned int textureId = 0;

public:
	Texture(const char* filepath);
	~Texture();

	unsigned int getId();
};
