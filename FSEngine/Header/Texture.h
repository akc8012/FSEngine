#pragma once
#include "Shading.h"
#include "FSException.h"

#include <SDL.h>
#include <SDL_image.h>
#include <GL\glew.h>
#include <SDL_opengl.h>

#include <string>
using std::string;
using glm::tvec2;

class Texture : public Shading
{
public:
	enum TextureType { Diffuse, Specular };

private:
	string filepath;
	Uint32 textureId = NULL;
	tvec2<int> surfaceSize;
	TextureType textureType = Diffuse;

	GLenum GetTextureFormat(Uint32 colors, Uint32 rmask) const;
	void FlipSurface(SDL_Surface* surface);
	int GetPixelIndex(int x, int y, int surfaceWidth) const;

	void DeleteTexture();

protected:
	void GenerateTexture(SDL_Surface* surface, bool flipSurface = false);

public:
	static const Types::ComponentType ComponentTypeId = Types::Texture;
	Types::ComponentType GetComponentTypeId() const override;

	Texture();
	Texture(const string& filepath);
	~Texture();

	void Load(const string& filepath);
	void BindTexture() override;

	TextureType GetTextureType() const;
	const tvec2<int>& GetSurfaceSize() const;

	json GetJson() const override;
	void SetFromJson(const json& j) override;
};
