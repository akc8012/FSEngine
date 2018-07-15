#pragma once
#include "GameObject.h"

#include <SDL.h>
#include <SDL_ttf.h>

using std::vector;
using std::string;

class RenderText : public GameObject
{
public:
	enum AnchorPosition { Center, TopLeft, TopRight, BottomLeft, BottomRight };

private:

	TTF_Font* font = nullptr;
	string renderText;
	vec2 aspectRatio;

	vec2 pixelScaleFactor = vec2(1.f, 1.f);
	vec2 pixelPosition = vec2(0, 0);
	AnchorPosition anchorPosition = Center;

	MeshComponent* CreateMeshComponent();
	void LoadFont(const char* fontName);
	void CreateTextureComponent(const string& text);

	vec2 CalculateAspectRatio(const vec2& surfaceSize);
	void SetScaleFromWindowSize(const vec2& windowSize);

	void SetPositionFromWindowSize(const vec2& windowSize);
	vec2 GetPixelAnchoredPosition(const vec2& windowSize) const;

	void SetPixelPositionToTopLeftOrigin();

public:
	RenderText(FileSystem* fileSystem, Input* input, Window* window);
	~RenderText();

	void Update(float deltaTime);
	void SetText(const string& text);

	void SetPixelScale(const vec2& pixelScaleFactor);
	void SetPixelScale(float pixelScaleFactor);
	void SetPixelPosition(const vec2& pixelPosition);
	void SetScreenAnchorPoint(AnchorPosition anchorPoint);
};
