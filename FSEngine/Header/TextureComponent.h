#pragma once
#include "Component.h"

#include <SDL.h>
#include <SDL_image.h>
#include <GL\glew.h>
#include <SDL_opengl.h>

#include <cstdlib>
#include <string>
#include <memory>

class TextureComponent : public Component
{
private:
	Uint32 textureId = NULL;
	std::string shaderType;

	GLenum GetTextureFormat(Uint32 colors, Uint32 rmask) const;

	void FlipSurface(SDL_Surface* surface);
	int GetPixelIndex(int x, int y, int surfaceWidth) const;

	void DeleteTexture();

public:
	TextureComponent(const char* filepath);
	TextureComponent(SDL_Surface* surface);
	~TextureComponent();

	void GenerateTexture(SDL_Surface* surface);
	void Bind();

	const type_info& GetType() const;
};
