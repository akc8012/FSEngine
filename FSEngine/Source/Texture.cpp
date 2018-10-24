#include "../Header/Texture.h"

Texture::Texture()
{

}

Texture::Texture(const string& filepath)
 : filepath(filepath)
{
	CreateTextureFromFilepath(filepath);
}

void Texture::CreateTextureFromFilepath(const string& filepath)
{
	SDL_Surface* surface = IMG_Load(filepath.c_str());
	if (surface == nullptr)
		throwFS((string)"Unable to load image at path: " + filepath + ", " + IMG_GetError());

	GenerateTexture(surface);
	SDL_FreeSurface(surface);
}

Texture::Texture(SDL_Surface* surface, bool flipSurface)
{
	GenerateTexture(surface, flipSurface);
}

void Texture::GenerateTexture(SDL_Surface* surface, bool flipSurface)
{
	DeleteTexture();

	const int Amount = 1;
	glGenTextures(Amount, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if (flipSurface)
		FlipSurface(surface);

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

void Texture::FlipSurface(SDL_Surface* surface)
{
	const int ExpectedColorDepth = 4;
	if (surface->format->BytesPerPixel != ExpectedColorDepth)
		throwFS((string)"Error loading texture: Cannot flip surface because it does not have 32 bits of color depth");

	const int PixelCount = surface->w * surface->h;
	Uint32* sourcePixels = (Uint32*)surface->pixels;
	unique_ptr<Uint32[]> targetPixels(new Uint32[PixelCount]);

	for (int row = 0; row < surface->h; row++)
	{
		int flippedRowIndex = abs(row - (surface->h - 1));

		for (int column = 0; column < surface->w; column++)
		{
			Uint32 pixel = sourcePixels[GetPixelIndex(column, row, surface->w)];
			targetPixels[GetPixelIndex(column, flippedRowIndex, surface->w)] = pixel;
		}
	}

	for (int i = 0; i < PixelCount; i++)
		sourcePixels[i] = targetPixels[i];
}

int Texture::GetPixelIndex(int x, int y, int surfaceWidth) const
{
	return (y * surfaceWidth) + x;
}

void Texture::BindTexture()
{
	glBindTexture(GL_TEXTURE_2D, textureId);
}

bool Texture::HasFlatColor() const
{
	return false;
}

Texture::TextureType Texture::GetTextureType() const
{
	return textureType;
}

json Texture::GetJson() const
{
	json j = Drawable::GetJson();
	j["type"] = Types::ComponentTypeString[ComponentTypeId];
	j["Filepath"] = filepath;
	j["TextureType"] = textureType;

	return j;
}

void Texture::SetFromJson(const json& j)
{
	Drawable::SetFromJson(j);

	filepath = j["Filepath"].get<string>();
	textureType = (TextureType)j["TextureType"].get<int>();

	DeleteTexture();
	CreateTextureFromFilepath(filepath);
}

Texture::~Texture()
{
	DeleteTexture();
}

void Texture::DeleteTexture()
{
	if (textureId != NULL)
	{
		const int Amount = 1;
		glDeleteTextures(Amount, &textureId);
		textureId = NULL;
	}
}

Types::ComponentType Texture::GetComponentTypeId() const
{
	return ComponentTypeId;
}
