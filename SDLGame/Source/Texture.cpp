#include "../Header/Texture.h"
#include <string>
using namespace std;

Texture::Texture(const char* filepath)
{
	SDL_Surface* surface = IMG_Load(filepath);
	if (surface == NULL)
		throw (string)"Unable to load image at path: " + filepath + ", " + IMG_GetError();

	SDL_FreeSurface(surface);
}
