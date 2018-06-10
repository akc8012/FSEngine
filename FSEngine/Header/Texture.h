#pragma once
#include <SDL_image.h>
#include <SDL.h>

#define uint unsigned int

class Texture
{
private:
	uint textureId = 0;

public:
	Texture(const char* filepath);
	~Texture();

	uint getTextureId();
};
