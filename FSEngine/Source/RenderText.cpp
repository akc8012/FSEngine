#include "../Header/RenderText.h"

RenderText::RenderText(FileSystem* fileSystem, Input* input, Window* window)
 : GameObject(fileSystem, input, window)
{
	AddComponent(new TransformComponent());
	AddComponent(CreateMeshComponent());

	LoadFont("arial.ttf");
	SetText(fileSystem->GetSettingsValue("RenderText").get<string>().c_str());
}

MeshComponent* RenderText::CreateMeshComponent()
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

	return new MeshComponent(vertices, indices);
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
	if (renderText != text || GetComponent<TextureComponent>() == nullptr)
		CreateTextureComponent(text);
}

void RenderText::CreateTextureComponent(const string& text)
{
	renderText = text;

	SDL_Color textColor = SDL_Color { 255, 255, 255, 255 };
	SDL_Surface* surface = TTF_RenderText_Blended(font, text == "" ? " " : text.c_str(), textColor);
	aspectRatio = CalculateAspectRatio(vec2(surface->w, surface->h));

	if (GetComponent<TextureComponent>() == nullptr)
		AddComponent(new TextureComponent(surface, true));
	else
		GetComponent<TextureComponent>()->GenerateTexture(surface, true);

	SDL_FreeSurface(surface);
}

vec2 RenderText::CalculateAspectRatio(const vec2& surfaceSize)
{
	float width = std::max((float)surfaceSize.x / (float)surfaceSize.y, 1.f);
	float height = std::max((float)surfaceSize.y / (float)surfaceSize.x, 1.f);

	return vec2(width, height);
}

void RenderText::Update(float deltaTime)
{
	SetText(fileSystem->GetSettingsValue("RenderText").get<string>());

	vec2 windowSize = window->GetWindowSize();
	SetScaleFromWindowSize(windowSize);
	SetPositionFromWindowSize(windowSize);
}

void RenderText::SetScaleFromWindowSize(const vec2& windowSize)
{
	float width = (aspectRatio.x * (1 / aspectRatio.y)) / windowSize.x;
	float height = 1 / windowSize.y;

	GetComponent<TransformComponent>()->SetScale(vec2(width, height));
	GetComponent<TransformComponent>()->Scale(pixelScaleFactor);
}

void RenderText::SetPositionFromWindowSize(const vec2& windowSize)
{
	vec2 anchorPixelPosition = GetPixelAnchoredPosition(windowSize);
	GetComponent<TransformComponent>()->SetPosition(vec2(anchorPixelPosition.x / windowSize.x, anchorPixelPosition.y / windowSize.y));
}

vec2 RenderText::GetPixelAnchoredPosition(const vec2& windowSize) const
{
	switch (anchorPosition)
	{
	case Center:
		return pixelPosition;
	case TopLeft:
		return vec2(pixelPosition.x - windowSize.x, pixelPosition.y + windowSize.y);
	case TopRight:
		return vec2(pixelPosition.x + windowSize.x, pixelPosition.y + windowSize.y);
	case BottomLeft:
		return vec2(pixelPosition.x - windowSize.x, pixelPosition.y - windowSize.y);
	case BottomRight:
		return vec2(pixelPosition.x + windowSize.x, pixelPosition.y - windowSize.y);
	default:
		throw "RenderText error: Could not recognize anchorPosition: " + std::to_string(anchorPosition);
	}
}

void RenderText::SetPixelScale(const vec2& pixelScaleFactor)
{
	this->pixelScaleFactor = pixelScaleFactor;
}

void RenderText::SetPixelScale(float pixelScaleFactor)
{
	this->pixelScaleFactor = vec2(pixelScaleFactor, pixelScaleFactor);
}

void RenderText::SetPixelPosition(const vec2& pixelPosition)
{
	this->pixelPosition = pixelPosition;
	SetPixelPositionToTopLeftOrigin();
}

void RenderText::SetPixelPositionToTopLeftOrigin()
{
	pixelPosition *= 2.f;
}

void RenderText::SetScreenAnchorPoint(AnchorPosition anchorPoint)
{
	this->anchorPosition = anchorPoint;
}

RenderText::~RenderText()
{
	TTF_CloseFont(font);
}
