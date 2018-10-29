#include "../Header/RenderText.h"

#pragma region Initialize
void RenderText::Start()
{
	LoadFont("consola.ttf");
	AddComponent(make_shared<Transform>())->SetSerializable(false);

	Mesh* meshComponent = AddComponent(make_shared<QuadMesh>());
	meshComponent->GetParameterCollection()->SetParameter(Mesh::DrawElements, false);
	meshComponent->GetParameterCollection()->SetParameter(Mesh::RenderBackfaces, true);

	systems->eventSystem->AddListener("SurfaceSizeChanged", this);
	GetParameterCollection()->SetParameter(DoDraw, false);
	GetParameterCollection()->SetParameter(DoLateDraw, true);
}

void RenderText::LoadFont(const string& fontName)
{
	const int FontSize = 32;
	font = TTF_OpenFont(((string)"Resource/Font/" + fontName).c_str(), FontSize);
	if (font == nullptr)
		throwFS((string)"Failed to load font! SDL_ttf error: " + TTF_GetError());
}
#pragma endregion

void RenderText::Update()
{

}

#pragma region Set Text
void RenderText::SetText(const string& text)
{
	if (renderText == text)
		return;

	SetTextSurface(text);
	SetTransformFromSurfaceSize(surfaceSize);
}

void RenderText::SetTextSurface(const string& text)
{
	renderText = text == "" ? " " : text;

	SDL_Color textColor = SDL_Color { 255, 255, 255, 255 };
	SDL_Surface* surface = TTF_RenderText_Blended(font, renderText.c_str(), textColor);
	aspectRatio = CalculateAspectRatio(vec2(surface->w, surface->h));

	if (TryGetComponent<Texture>() == nullptr)
		CreateTextureComponent(surface);
	else
		GetComponent<Texture>()->GenerateTexture(surface, true);

	SDL_FreeSurface(surface);
}

void RenderText::CreateTextureComponent(SDL_Surface* surface)
{
	Texture* texture = AddComponent(make_shared<Texture>(surface, true));
	texture->GetParameterCollection()->SetParameter(Drawable::RenderPerspective, false);
	texture->GetParameterCollection()->SetParameter(Drawable::EnableDepthTest, false);

	GetParameterCollection()->SetParameter(DoDraw, true);
}

vec2 RenderText::CalculateAspectRatio(const vec2& surfaceSize)
{
	float width = std::max((float)surfaceSize.x / (float)surfaceSize.y, 1.f);
	float height = std::max((float)surfaceSize.y / (float)surfaceSize.x, 1.f);

	return vec2(width, height);
}
#pragma endregion

void RenderText::ReceiveEvent(const string& key, const json& event)
{
	if (key != "SurfaceSizeChanged")
		return;

	surfaceSize = vec2 { event[0], event[1] };
	SetTransformFromSurfaceSize(surfaceSize);
}

#pragma region Set Transform From Surface Size
void RenderText::SetTransformFromSurfaceSize(const vec2& surfaceSize)
{
	SetScaleFromSurfaceSize(surfaceSize);
	SetPositionFromSurfaceSize(surfaceSize);
}

void RenderText::SetScaleFromSurfaceSize(const vec2& surfaceSize)
{
	float width = (aspectRatio.x * (1 / aspectRatio.y)) / surfaceSize.x;
	float height = 1 / surfaceSize.y;

	GetComponent<Transform>()->SetScale(vec2(width, height));

	const float AdjustmentForQuadSize = 2.f;
	GetComponent<Transform>()->Scale(pixelScaleFactor * AdjustmentForQuadSize);
}

void RenderText::SetPositionFromSurfaceSize(const vec2& surfaceSize)
{
	vec2 alignedPixelPosition = GetPixelAlignPosition(GetPixelAnchoredPosition(surfaceSize), surfaceSize);
	GetComponent<Transform>()->SetPosition(vec2(alignedPixelPosition.x / surfaceSize.x, alignedPixelPosition.y / surfaceSize.y));
}

vec2 RenderText::GetPixelAnchoredPosition(const vec2& surfaceSize) const
{
	const float AdjustmentForTopLeftOrigin = 2.f;
	vec2 position = pixelPosition * AdjustmentForTopLeftOrigin;

	switch (anchorPosition)
	{
	case Center:
		return position;
	case TopLeft:
		return vec2(position.x - surfaceSize.x, position.y + surfaceSize.y);
	case TopRight:
		return vec2(position.x + surfaceSize.x, position.y + surfaceSize.y);
	case BottomLeft:
		return vec2(position.x - surfaceSize.x, position.y - surfaceSize.y);
	case BottomRight:
		return vec2(position.x + surfaceSize.x, position.y - surfaceSize.y);
	default:
		throwFS("Could not recognize anchorPosition: " + std::to_string(anchorPosition));
	}
}

vec2 RenderText::GetPixelAlignPosition(const vec2& position, const vec2& surfaceSize) const
{
	const float AdjustmentForQuadSize = 0.5f;
	vec2 pixelScale = GetPixelScale(surfaceSize) * AdjustmentForQuadSize;

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

vec2 RenderText::GetPixelScale(const vec2& surfaceSize) const
{
	Transform* transform = GetComponent<Transform>();
	return vec2(transform->GetScale().x * surfaceSize.x, transform->GetScale().y * surfaceSize.y);
}
#pragma endregion

#pragma region Public Setters
void RenderText::SetPixelScale(const vec2& pixelScaleFactor)
{
	this->pixelScaleFactor = pixelScaleFactor;
	SetTransformFromSurfaceSize(surfaceSize);
}

void RenderText::SetPixelScale(float pixelScaleFactor)
{
	this->pixelScaleFactor = vec2(pixelScaleFactor, pixelScaleFactor);
	SetTransformFromSurfaceSize(surfaceSize);
}

void RenderText::SetPixelPosition(const vec2& pixelPosition)
{
	this->pixelPosition = pixelPosition;
	SetTransformFromSurfaceSize(surfaceSize);
}

void RenderText::SetScreenAnchorPoint(AnchorPosition anchorPoint)
{
	this->anchorPosition = anchorPoint;
	SetTransformFromSurfaceSize(surfaceSize);
}

void RenderText::SetTextAlignment(AnchorPosition alignPosition)
{
	this->alignPosition = alignPosition;
	SetTransformFromSurfaceSize(surfaceSize);
}
#pragma endregion

json RenderText::GetJson() const
{
	json j = GameObject::GetJson();

	j["RenderText"] = renderText;
	j["ScreenAnchorPoint"] = anchorPosition;
	j["TextAlignment"] = alignPosition;
	j["PixelPosition"] = json { pixelPosition.x, pixelPosition.y };
	j["PixelScale"] = json { pixelScaleFactor.x, pixelScaleFactor.y };

	return j;
}

void RenderText::SetFromJson(const json& j)
{
	GameObject::SetFromJson(j);

	SetText(j["RenderText"].get<string>());
	SetScreenAnchorPoint((AnchorPosition)j["ScreenAnchorPoint"].get<int>());
	SetTextAlignment((AnchorPosition)j["TextAlignment"].get<int>());
	SetPixelPosition(vec2(j["PixelPosition"][0], j["PixelPosition"][1]));
	SetPixelScale(vec2(j["PixelScale"][0], j["PixelScale"][1]));
}

string RenderText::GetGameObjectType() const
{
	return "RenderText";
}

RenderText::~RenderText()
{
	TTF_CloseFont(font);
}
