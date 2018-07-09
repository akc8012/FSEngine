#pragma once
#include "Component.h"

#include <SDL.h>
#include <SDL_image.h>
#include <GL\glew.h>
#include <SDL_opengl.h>

#include <cstdlib>
#include <string>
#include <memory>
using std::string;
using std::unique_ptr;

class TextureComponent : public Component
{
private:
	Uint32 textureId = NULL;
	string filepath = "";

	GLenum GetTextureFormat(Uint32 colors, Uint32 rmask) const;

	void FlipSurface(SDL_Surface* surface);
	int GetPixelIndex(int x, int y, int surfaceWidth) const;

	void DeleteTexture();

public:
	TextureComponent(const char* filepath);
	TextureComponent(SDL_Surface* surface, bool flipSurface = false);
	~TextureComponent();

	void GenerateTexture(SDL_Surface* surface, bool flipSurface = false);
	void BindTexture();

	string GetFilepath() const;
	const type_info& GetType() const;
};
