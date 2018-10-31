#pragma once
#include "Texture.h"

#include <SDL.h>
#include <SDL_ttf.h>

class FontTexture : public Texture
{
private:
	TTF_Font* font = nullptr;

public:
	FontTexture();
	~FontTexture();

	void LoadFont(const string& fontName);
	void GenerateFontTexture(const string& text);
};
