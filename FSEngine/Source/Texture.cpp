#include "../Header/Texture.h"
#include <GL\glew.h>
#include <SDL_opengl.h>
#include <GL\GLU.h>
#include <string>
using namespace std;

Texture::Texture(const char* filepath)
{
	SDL_Surface* surface = IMG_Load(filepath);
	if (surface == NULL)
		throw (string)"Unable to load image at path: " + filepath + ", " + IMG_GetError();

	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	const int MipmapLevel = 0, Border = 0;
	glTexImage2D(GL_TEXTURE_2D, MipmapLevel, GL_RGB, surface->w, surface->h, Border, GL_RGB, GL_UNSIGNED_BYTE, surface->pixels);
	glGenerateMipmap(GL_TEXTURE_2D);

	SDL_FreeSurface(surface);
}

unsigned int Texture::getId()
{
	return textureId;
}

Texture::~Texture()
{
	glDeleteTextures(1, &textureId);
}
