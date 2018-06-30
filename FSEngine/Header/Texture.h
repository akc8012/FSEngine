#pragma once
#include <SDL_image.h>
#include <SDL.h>
#include <GL\glew.h>
#include <SDL_opengl.h>

#include <cstdlib>
#include <string>

class Texture
{
private:
	Uint32 textureId = NULL;

	GLenum GetTextureFormat(Uint32 colors, Uint32 rmask) const;

	void FlipSurface(SDL_Surface* surface);
	int GetPixelIndex(int x, int y, int surfaceWidth) const;

	void DeleteTexture();

public:
	Texture(const char* filepath);
	Texture(SDL_Surface* surface);

	void GenerateTexture(SDL_Surface* surface);

	~Texture();

	Uint32 GetId() const;
};
