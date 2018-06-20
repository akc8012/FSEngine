#pragma once
#include <SDL_image.h>
#include <SDL.h>

class Texture
{
private:
	unsigned int textureId = NULL;

public:
	Texture(const char* filepath);
	~Texture();

	unsigned int GetId();
};
