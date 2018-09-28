#pragma once
#include "Shading.h"

#include <SDL.h>
#include <SDL_image.h>
#include <GL\glew.h>
#include <SDL_opengl.h>

#include <string>
using std::string;

class TextureComponent : public Shading
{
public:
	enum TextureType { Diffuse, Specular };

private:
	Uint32 textureId = NULL;
	TextureType textureType = Diffuse;

	GLenum GetTextureFormat(Uint32 colors, Uint32 rmask) const;
	void FlipSurface(SDL_Surface* surface);
	int GetPixelIndex(int x, int y, int surfaceWidth) const;

	void DeleteTexture();

public:
	TextureComponent(const string& filepath);
	TextureComponent(SDL_Surface* surface, bool flipSurface = false);
	~TextureComponent();

	void BindTexture();
	void GenerateTexture(SDL_Surface* surface, bool flipSurface = false);

	TextureType GetTextureType() const;
};
