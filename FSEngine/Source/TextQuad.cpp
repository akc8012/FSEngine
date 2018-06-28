#include "../Header/TextQuad.h"

TextQuad::TextQuad()
{
	font = TTF_OpenFont("Resource/Font/arial.ttf", 18);
	if (font == NULL)
		throw (string)"Failed to load font! SDL_ttf error: " + TTF_GetError();
}

TextQuad::~TextQuad()
{
	TTF_CloseFont(font);
}
