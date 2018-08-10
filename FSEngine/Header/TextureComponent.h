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

#include <glm\glm.hpp>
using namespace glm;

class TextureComponent : public Component
{
public:
	enum TextureType { Diffuse, Specular };

private:
	Uint32 textureId = NULL;
	TextureType textureType = Diffuse;
	string name = "";
	vec4 flatColor = vec4(0);

	void SetName(const string& filepath, const string& name);
	GLenum GetTextureFormat(Uint32 colors, Uint32 rmask) const;

	void FlipSurface(SDL_Surface* surface);
	int GetPixelIndex(int x, int y, int surfaceWidth) const;

	void DeleteTexture();

public:
	static const ComponentType ComponentTypeId = Texture;

	TextureComponent(const string& filepath, const string& name = "");
	TextureComponent(SDL_Surface* surface, bool flipSurface = false);
	~TextureComponent();

	void GenerateTexture(SDL_Surface* surface, bool flipSurface = false);
	void SetFlatColor(vec4 flatColor);
	void BindTexture();

	string GetName() const;
	TextureType GetTextureType() const;

	bool HasFlatColor() const;
	vec4 GetFlatColor() const;
};
