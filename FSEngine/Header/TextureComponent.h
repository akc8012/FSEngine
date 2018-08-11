#pragma once
#include "ShadingComponent.h"

#include <SDL.h>
#include <SDL_image.h>
#include <GL\glew.h>
#include <SDL_opengl.h>

#include <cstdlib>
#include <string>
#include <memory>
using std::string;
using std::unique_ptr;

class TextureComponent : public ShadingComponent
{
public:
	enum TextureType { Diffuse, Specular };

private:
	Uint32 textureId = NULL;
	TextureType textureType = Diffuse;
	string name = "";

	void SetName(const string& filepath, const string& name);
	GLenum GetTextureFormat(Uint32 colors, Uint32 rmask) const;

	void FlipSurface(SDL_Surface* surface);
	int GetPixelIndex(int x, int y, int surfaceWidth) const;

	void DeleteTexture();

public:
	TextureComponent(const string& filepath, const string& name = "");
	TextureComponent(SDL_Surface* surface, bool flipSurface = false);
	~TextureComponent();

	bool CanUse() const;
	void Use(ShaderProgram* shaderProgram);
	void GenerateTexture(SDL_Surface* surface, bool flipSurface = false);

	string GetName() const;
	TextureType GetTextureType() const;
};
