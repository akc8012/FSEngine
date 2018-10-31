#pragma once
#include "Texture.h"

#include <SDL.h>
#include <SDL_ttf.h>

class FontTexture : public Texture
{
private:
	TTF_Font* font = nullptr;
	string text;

public:
	FontTexture();
	~FontTexture();

	void LoadFont(const string& fontName);
	void GenerateFontTexture(const string& text);

	const string& GetText() const;

	json GetJson() const override;
	void SetFromJson(const json& j) override;
};
