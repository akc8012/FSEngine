#include "../Header/TextQuad.h"

TextQuad::TextQuad(FileSystem* fileSystem)
 : GameObject(fileSystem)
{
	using std::string;

	AddComponent(new TransformComponent());

	LoadFont("arial.ttf");
	SetText(fileSystem->GetSettingsValue("RenderText").get<string>().c_str());

	CreateRenderComponent();
}

void TextQuad::LoadFont(const char* fontName)
{
	using std::string;

	const int FontSize = 32;
	font = TTF_OpenFont(((string)"Resource/Font/" + fontName).c_str(), FontSize);
	if (font == nullptr)
		throw (string)"Failed to load font! SDL_ttf error: " + TTF_GetError();
}

void TextQuad::CreateTexture(const char* text)
{
	renderText = text;
	SDL_Surface* surface = TTF_RenderText_Blended(font, renderText.c_str(), SDL_Color { 0, 0, 0, 255 });
	textAspect = (float)surface->h / (float)surface->w;

	if (GetComponent<TextureComponent>() == nullptr)
		AddComponent(new TextureComponent(surface));
	else
		GetComponent<TextureComponent>()->GenerateTexture(surface);

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
	AddComponent(new RenderComponent(vertices, indices, Stride));
}

void TextQuad::Update(Uint32 deltaTime)
{
	SetText(fileSystem->GetSettingsValue("RenderText").get<std::string>());
}

void TextQuad::SetText(std::string text)
{
	if (renderText != text)
	{
		CreateTexture(text.c_str());

		const float ScaleFactor = 0.2f;
		GetComponent<TransformComponent>()->SetScale(vec3(ScaleFactor, ScaleFactor * textAspect, 1));
	}
}

TextQuad::~TextQuad()
{
	TTF_CloseFont(font);
}
