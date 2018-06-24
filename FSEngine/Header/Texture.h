#pragma once
#include <SDL_image.h>
#include <SDL.h>
#include <GL\glew.h>
#include <SDL_opengl.h>

#include <string>
using namespace std;

class Texture
{
private:
	Uint32 textureId = NULL;

public:
	Texture(const char* filepath);
	~Texture();

	Uint32 GetId();
};
