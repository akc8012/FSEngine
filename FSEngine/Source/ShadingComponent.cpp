#include "../Header/ShadingComponent.h"

ShadingComponent::ShadingComponent(const string& filepath, const string& name)
{
	SetName(filepath, name);

	SDL_Surface* surface = IMG_Load(filepath.c_str());
	if (surface == nullptr)
		throw (string)"Unable to load image at path: " + filepath + ", " + IMG_GetError();

	GenerateTexture(surface);
	SDL_FreeSurface(surface);
}

void ShadingComponent::SetName(const string& filepath, const string& name)
{
	if (name == "")
		this->name = filepath.substr(filepath.find_last_of('/') + 1, filepath.length());
	else
		this->name = name;
}

ShadingComponent::ShadingComponent(SDL_Surface* surface, bool flipSurface)
{
	GenerateTexture(surface, flipSurface);
}

void ShadingComponent::GenerateTexture(SDL_Surface* surface, bool flipSurface)
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

GLenum ShadingComponent::GetTextureFormat(Uint32 colors, Uint32 rmask) const
{
	bool hasAlphaChannel = colors == 4;
	bool isStandardRMask = rmask == 0x000000ff;

	if (hasAlphaChannel)
		return isStandardRMask ? GL_RGBA : GL_BGRA;
	else
		return isStandardRMask ? GL_RGB : GL_BGR;
}

void ShadingComponent::FlipSurface(SDL_Surface* surface)
{
	const int ExpectedColorDepth = 4;
	if (surface->format->BytesPerPixel != ExpectedColorDepth)
		throw (string)"Error loading texture: Cannot flip surface because it does not have 32 bits of color depth";

	const int PixelCount = surface->w * surface->h;
	Uint32* sourcePixels = (Uint32*)surface->pixels;
	unique_ptr<Uint32[]> targetPixels(new Uint32[PixelCount]);

	for (int row = 0; row < surface->h; row++)
	{
		int flippedRowIndex = abs(row - (surface->h-1));

		for (int column = 0; column < surface->w; column++)
		{
			Uint32 pixel = sourcePixels[GetPixelIndex(column, row, surface->w)];
			targetPixels[GetPixelIndex(column, flippedRowIndex, surface->w)] = pixel;
		}
	}

	for (int i = 0; i < PixelCount; i++)
		sourcePixels[i] = targetPixels[i];
}

int ShadingComponent::GetPixelIndex(int x, int y, int surfaceWidth) const
{
	return (y * surfaceWidth) + x;
}

void ShadingComponent::SetFlatColor(vec4 flatColor)
{
	this->flatColor = flatColor;
}

void ShadingComponent::BindTexture()
{
	glBindTexture(GL_TEXTURE_2D, textureId);
}

string ShadingComponent::GetName() const
{
	return name;
}

ShadingComponent::TextureType ShadingComponent::GetTextureType() const
{
	return textureType;
}

bool ShadingComponent::HasFlatColor() const
{
	return flatColor != vec4(0);
}

vec4 ShadingComponent::GetFlatColor() const
{
	return flatColor;
}

ShadingComponent::~ShadingComponent()
{
	DeleteTexture();
}

void ShadingComponent::DeleteTexture()
{
	if (textureId != NULL)
	{
		const int Amount = 1;
		glDeleteTextures(Amount, &textureId);
	}
}
