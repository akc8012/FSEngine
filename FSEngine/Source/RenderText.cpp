#include "../Header/RenderText.h"

RenderText::RenderText(FileSystem* fileSystem, Input* input)
 : GameObject(fileSystem, input)
{
	AddComponent(new TransformComponent());

	LoadFont("arial.ttf");
	SetText(fileSystem->GetSettingsValue("RenderText").get<string>().c_str());

	CreateMeshComponent();
}

void RenderText::LoadFont(const char* fontName)
{
	const int FontSize = 32;
	font = TTF_OpenFont(((string)"Resource/Font/" + fontName).c_str(), FontSize);
	if (font == nullptr)
		throw (string)"Failed to load font! SDL_ttf error: " + TTF_GetError();
}

void RenderText::SetText(const string& text)
{
	if (renderText != text)
	{
		CreateTextureComponent(text.c_str());

		const float ScaleFactor = 0.2f;
		GetComponent<TransformComponent>()->SetScale(vec3(ScaleFactor, ScaleFactor * textAspect, 1));
	}
}

void RenderText::CreateTextureComponent(const char* text)
{
	renderText = text;
	SDL_Surface* surface = TTF_RenderText_Blended(font, renderText.c_str(), SDL_Color { 0, 0, 0, 255 });
	textAspect = (float)surface->h / (float)surface->w;

	if (GetComponent<TextureComponent>() == nullptr)
		AddComponent(new TextureComponent(surface, true));
	else
		GetComponent<TextureComponent>()->GenerateTexture(surface, true);

	SDL_FreeSurface(surface);
}

void RenderText::CreateMeshComponent()
{
	vector<float> rawVertices =
	{
		 // positions        // texture coords
		-1.0f, -1.0f, 0.0f,  0.0f, 0.0f,
		 1.0f, -1.0f, 0.0f,  1.0f, 0.0f,
		 1.0f,  1.0f, 0.0f,  1.0f, 1.0f,
		 1.0f,  1.0f, 0.0f,  1.0f, 1.0f,
		-1.0f,  1.0f, 0.0f,  0.0f, 1.0f,
		-1.0f, -1.0f, 0.0f,  0.0f, 0.0f
	};

	vector<Vertex> vertices;
	const int Stride = 5;
	for (int i = 0; i < rawVertices.size(); i += Stride)
	{
		Vertex vertex;
		vertex.position = vec3(rawVertices[i], rawVertices[i + 1], rawVertices[i + 2]);
		vertex.textureCoord = vec2(rawVertices[i + 3], rawVertices[i + 4]);

		vertices.push_back(vertex);
	}

	vector<Uint32> indices =
	{
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	AddComponent(new MeshComponent(vertices, indices));
}

void RenderText::Update(float deltaTime)
{
	SetText(fileSystem->GetSettingsValue("RenderText").get<string>());
}

RenderText::~RenderText()
{
	TTF_CloseFont(font);
}
