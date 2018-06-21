#include "../Header/Texture.h"

Texture::Texture(const char* filepath)
{
	SDL_Surface* surface = IMG_Load(filepath);
	if (surface == NULL)
		throw (string)"Unable to load image at path: " + filepath + ", " + IMG_GetError();

	const int Amount = 1;
	glGenTextures(Amount, &textureId);
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

unsigned int Texture::GetId()
{
	return textureId;
}

Texture::~Texture()
{
	const int Amount = 1;
	glDeleteTextures(Amount, &textureId);
}
