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
public:
	enum TextureType { Diffuse, Specular };

private:
	Uint32 textureId = NULL;
	TextureType textureType = Diffuse;
	string filename = "";

	GLenum GetTextureFormat(Uint32 colors, Uint32 rmask) const;

	void FlipSurface(SDL_Surface* surface);
	int GetPixelIndex(int x, int y, int surfaceWidth) const;

	void DeleteTexture();

public:
	TextureComponent(const string& filepath);
	TextureComponent(SDL_Surface* surface, bool flipSurface = false);
	~TextureComponent();

	void GenerateTexture(SDL_Surface* surface, bool flipSurface = false);
	void BindTexture();
	void SetTextureType(TextureType textureType);

	string GetFilename() const;
	TextureType GetTextureType() const;
	const type_info& GetType() const;
};
