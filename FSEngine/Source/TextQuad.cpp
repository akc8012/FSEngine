#include "../Header/TextQuad.h"

TextQuad::TextQuad(FileSystem* fileSystem)
 : GameObject(fileSystem)
{
	using std::string;

	transformComponent = new TransformComponent();

	LoadFont("arial.ttf");
	CreateTexture(fileSystem->GetSettingsValue("RenderText").get<string>().c_str());
	transformComponent->SetScale(vec3(1, 1.f * textAspect, 1));

	CreateRenderComponent();
}

void TextQuad::LoadFont(const char* fontName)
{
	using std::string;

	const int FontSize = 80;
	font = TTF_OpenFont(((string)"Resource/Font/" + fontName).c_str(), FontSize);
	if (font == nullptr)
		throw (string)"Failed to load font! SDL_ttf error: " + TTF_GetError();
}

void TextQuad::CreateTexture(const char* text)
{
	renderText = text;
	SDL_Surface* surface = TTF_RenderText_Blended(font, renderText.c_str(), SDL_Color { 0, 0, 0, 255 });
	textAspect = (float)surface->h / (float)surface->w;

	if (texture == nullptr)
		texture = new Texture(surface);
	else
		texture->GenerateTexture(surface);

	SDL_FreeSurface(surface);
}

void TextQuad::CreateRenderComponent()
{
	using std::vector;

	vector<float> vertices =
	{
		 // positions        // texture coords
		-1.0f, -1.0f, 0.0f,  0.0f, 0.0f,
		 1.0f, -1.0f, 0.0f,  1.0f, 0.0f,
		 1.0f,  1.0f, 0.0f,  1.0f, 1.0f,
		 1.0f,  1.0f, 0.0f,  1.0f, 1.0f,
		-1.0f,  1.0f, 0.0f,  0.0f, 1.0f,
		-1.0f, -1.0f, 0.0f,  0.0f, 0.0f
	};

	vector<Uint32> indices =
	{
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	const Uint32 Stride = 5;
	renderComponent = new RenderComponent(texture, vertices, indices, Stride);
}

void TextQuad::SetText(std::string text)
{
	if (renderText != text)
	{
		CreateTexture(text.c_str());
		transformComponent->SetScale(vec3(1, 1.f * textAspect, 1));
	}
}

TextQuad::~TextQuad()
{
	delete texture;
	TTF_CloseFont(font);
}
