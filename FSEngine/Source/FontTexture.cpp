#include "../Header/FontTexture.h"

FontTexture::FontTexture()
{
	GetParameterCollection()->SetParameter(Shading::RenderPerspective, false);
	GetParameterCollection()->SetParameter(Shading::EnableDepthTest, false);
}

void FontTexture::LoadFont(const string& fontName)
{
	const int FontSize = 32;
	font = TTF_OpenFont(((string)"Resource/Font/" + fontName).c_str(), FontSize);
	if (font == nullptr)
		throwFS((string)"Failed to load font! SDL_ttf error: " + TTF_GetError());
}

void FontTexture::GenerateFontTexture(const string& text)
{
	this->text = text;
	SDL_Color textColor = SDL_Color { 255, 255, 255, 255 };

	SDL_Surface* surface = TTF_RenderText_Blended(font, (text == "" ? " " : text).c_str(), textColor);
	GenerateTexture(surface, true);

	SDL_FreeSurface(surface);
}

const string& FontTexture::GetText() const
{
	return text;
}

json FontTexture::GetJson() const
{
	json j = Texture::GetJson();
	j["Text"] = text;

	return j;
}

void FontTexture::SetFromJson(const json& j)
{
	Texture::SetFromJson(j);

	string jsonText = j["Text"].get<string>();
	if (jsonText != text)
		GenerateFontTexture(jsonText);
}

FontTexture::~FontTexture()
{
	TTF_CloseFont(font);
}
