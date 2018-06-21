#pragma once
#include <SDL_image.h>
#include <SDL.h>
#include <GL\glew.h>
#include <SDL_opengl.h>
#include <GL\GLU.h>

#include <string>
using namespace std;

class Texture
{
private:
	unsigned int textureId = NULL;

public:
	Texture(const char* filepath);
	~Texture();

	unsigned int GetId();
};
