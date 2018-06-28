#pragma once
#include "GameObject.h"

#include <SDL.h>
#include <SDL_ttf.h>

class TextQuad : public GameObject
{
private:
	TTF_Font* font;
	Texture* texture;

public:
	TextQuad();
	~TextQuad();

};
