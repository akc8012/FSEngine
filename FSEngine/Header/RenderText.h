#pragma once
#include "GameObject.h"

#include <SDL.h>
#include <SDL_ttf.h>

using std::vector;
using std::string;

class RenderText : public GameObject
{
private:
	TTF_Font* font = nullptr;
	string renderText;
	vec2 aspectRatio;
	vec2 pixelScaleFactor = vec2(1.f, 1.f);

	MeshComponent* CreateMeshComponent();
	void LoadFont(const char* fontName);
	void CreateTextureComponent(const string& text);

	vec2 CalculateAspectRatio(const vec2& surfaceSize);
	void SetScaleFromWindowSize();

public:
	RenderText(FileSystem* fileSystem, Input* input, Window* window);
	~RenderText();

	void Update(float deltaTime);
	void SetText(const string& text);

	void SetPixelScale(const vec2& pixelScaleFactor);
	void SetPixelScale(float pixelScaleFactor);
};
