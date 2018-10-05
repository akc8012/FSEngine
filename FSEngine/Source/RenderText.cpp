#include "../Header/RenderText.h"

RenderText::RenderText(Window* window)
{
	this->window = window;
}

void RenderText::Start()
{
	components->transform->Add(GetName(), make_shared<Transform>());
	shared_ptr<Mesh> meshComponent = components->mesh->Add(GetName(), CreateMeshComponent());
	meshComponent->GetParameterCollection()->SetParameter(Mesh::DrawElements, false);
	meshComponent->GetParameterCollection()->SetParameter(Mesh::RenderBackfaces, true);

	LoadFont("arial.ttf");

	SetText(renderText);
	GetComponent<Shading>()->GetParameterCollection()->SetParameter(Shading::RenderPerspective, false);
	GetComponent<Shading>()->GetParameterCollection()->SetParameter(Shading::EnableDepthTest, false);
}

shared_ptr<Mesh> RenderText::CreateMeshComponent() const
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

	vector<Uint32> indices =
	{
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	const int Stride = 5;
	return make_shared<Mesh>(rawVertices, Stride, indices);
}

void RenderText::LoadFont(const string& fontName)
{
	const int FontSize = 32;
	font = TTF_OpenFont(((string)"Resource/Font/" + fontName).c_str(), FontSize);
	if (font == nullptr)
		throwFS((string)"Failed to load font! SDL_ttf error: " + TTF_GetError());
}

void RenderText::SetText(const string& text)
{
	if (renderText != text || components->shading->TryGet(GetName()) == nullptr)
		CreateTextureComponent(text);
}

void RenderText::CreateTextureComponent(const string& text)
{
	renderText = text;

	SDL_Color textColor = SDL_Color { 255, 255, 255, 255 };
	SDL_Surface* surface = TTF_RenderText_Blended(font, text == "" ? " " : text.c_str(), textColor);
	aspectRatio = CalculateAspectRatio(vec2(surface->w, surface->h));

	if (components->shading->TryGet(GetName()) == nullptr)
		components->shading->Add(GetName(), make_shared<Texture>(surface, true));
	else
		dynamic_cast<Texture*>(components->shading->TryGet(GetName()).get())->GenerateTexture(surface, true);

	SDL_FreeSurface(surface);
}

vec2 RenderText::CalculateAspectRatio(const vec2& surfaceSize)
{
	float width = std::max((float)surfaceSize.x / (float)surfaceSize.y, 1.f);
	float height = std::max((float)surfaceSize.y / (float)surfaceSize.x, 1.f);

	return vec2(width, height);
}

void RenderText::Update()
{
	vec2 windowSize = window->GetWindowSize();
	SetScaleFromWindowSize(windowSize);
	SetPositionFromWindowSize(windowSize);
}

void RenderText::SetScaleFromWindowSize(const vec2& windowSize)
{
	float width = (aspectRatio.x * (1 / aspectRatio.y)) / windowSize.x;
	float height = 1 / windowSize.y;

	GetComponent<Transform>()->SetScale(vec2(width, height));
	GetComponent<Transform>()->Scale(pixelScaleFactor);
}

void RenderText::SetPositionFromWindowSize(const vec2& windowSize)
{
	vec2 alignedPixelPosition = GetPixelAlignPosition(GetPixelAnchoredPosition(windowSize), windowSize);
	GetComponent<Transform>()->SetPosition(vec2(alignedPixelPosition.x / windowSize.x, alignedPixelPosition.y / windowSize.y));
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
		throwFS("Could not recognize anchorPosition: " + std::to_string(anchorPosition));
	}
}

vec2 RenderText::GetPixelAlignPosition(const vec2& position, const vec2& windowSize) const
{
	vec2 pixelScale = GetPixelScale(windowSize);
	switch (alignPosition)
	{
	case Center:
		return position;
	case TopLeft:
		return vec2(position.x + pixelScale.x, position.y - pixelScale.y);
	case TopRight:
		return vec2(position.x - pixelScale.x, position.y - pixelScale.y);
	case BottomLeft:
		return vec2(position.x + pixelScale.x, position.y + pixelScale.y);
	case BottomRight:
		return vec2(position.x - pixelScale.x, position.y + pixelScale.y);
	default:
		throwFS("Could not recognize alignPosition: " + std::to_string(alignPosition));
	}
}

vec2 RenderText::GetPixelScale(const vec2& windowSize) const
{
	Transform* transform = GetComponent<Transform>();
	return vec2(transform->GetScale().x * windowSize.x, transform->GetScale().y * windowSize.y);
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

void RenderText::SetTextAlignment(AnchorPosition alignPosition)
{
	this->alignPosition = alignPosition;
}

RenderText::~RenderText()
{
	TTF_CloseFont(font);
}
