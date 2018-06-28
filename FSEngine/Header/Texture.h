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
	void GenerateTexture(SDL_Surface* surface);
	GLenum GetTextureFormat(Uint32 colors, Uint32 rmask) const;

public:
	Texture(const char* filepath);
	Texture(SDL_Surface* surface);
	~Texture();

	Uint32 GetId() const;
};
