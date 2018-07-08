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
	float textAspect;

	void LoadFont(const char* fontName);
	void CreateTextureComponent(const char* text);
	void CreateMeshComponent();

	void SetText(const string& text);

public:
	RenderText(FileSystem* fileSystem, Input* input);
	~RenderText();

	void Update(float deltaTime);
};
