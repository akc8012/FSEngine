#include "../Header/Texture.h"

Texture::Texture(const char* filepath)
{
	SDL_Surface* surface = IMG_Load(((string)"Resource/Image/" + filepath).c_str());
	if (surface == nullptr)
		throw (string)"Unable to load image at path: " + filepath + ", " + IMG_GetError();

	GenerateTexture(surface);
	SDL_FreeSurface(surface);
}

Texture::Texture(SDL_Surface* surface)
{
	GenerateTexture(surface);
}

void Texture::GenerateTexture(SDL_Surface* surface)
{
	const int Amount = 1;
	glGenTextures(Amount, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	const int MipmapLevel = 0, Border = 0;
	Uint32 colors = surface->format->BytesPerPixel;
	GLenum textureFormat = GetTextureFormat(colors, surface->format->Rmask);

	glTexImage2D(GL_TEXTURE_2D, MipmapLevel, colors, surface->w, surface->h, Border, textureFormat, GL_UNSIGNED_BYTE, surface->pixels);
	glGenerateMipmap(GL_TEXTURE_2D);
}

GLenum Texture::GetTextureFormat(Uint32 colors, Uint32 rmask) const
{
	bool hasAlphaChannel = colors == 4;
	bool isStandardRMask = rmask == 0x000000ff;

	if (hasAlphaChannel)
		return isStandardRMask ? GL_RGBA : GL_BGRA;
	else
		return isStandardRMask ? GL_RGB : GL_BGR;
}

Uint32 Texture::GetId() const
{
	return textureId;
}

Texture::~Texture()
{
	const int Amount = 1;
	glDeleteTextures(Amount, &textureId);
}
