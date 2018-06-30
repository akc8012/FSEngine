#pragma once
#include "GameObject.h"

#include <SDL.h>
#include <SDL_ttf.h>

class TextQuad : public GameObject
{
private:
	TTF_Font* font = nullptr;
	Texture* texture = nullptr;

public:
	TextQuad(FileSystem* fileSystem);
	~TextQuad();
};
