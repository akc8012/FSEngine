#include "../Header/Transform2D.h"

Types::ComponentType Transform2D::GetComponentTypeId() const
{
	return ComponentTypeId;
}

#pragma region Set Transform
void Transform2D::SetTransform(const vec2& windowSurfaceSize, const vec2& targetSurfaceSize)
{
	this->surfaceSize = windowSurfaceSize;
	this->targetSurfaceSize = targetSurfaceSize;

	SetScaleFromSurfaceSize(surfaceSize, CalculateAspectRatio(targetSurfaceSize));
	SetPositionFromSurfaceSize(surfaceSize);
}

vec2 Transform2D::CalculateAspectRatio(const vec2& surfaceSize) const
{
	float width = std::max((float)surfaceSize.x / (float)surfaceSize.y, 1.f);
	float height = std::max((float)surfaceSize.y / (float)surfaceSize.x, 1.f);

	return vec2(width, height);
}

void Transform2D::SetScaleFromSurfaceSize(const vec2& surfaceSize, const vec2& aspectRatio)
{
	float width = (aspectRatio.x * (1 / aspectRatio.y)) / surfaceSize.x;
	float height = 1 / surfaceSize.y;

	SetScale(vec2(width, height));

	const float AdjustmentForQuadSize = 2.f;
	Scale(pixelScaleFactor * AdjustmentForQuadSize);
}

void Transform2D::SetPositionFromSurfaceSize(const vec2& surfaceSize)
{
	vec2 alignedPixelPosition = GetPixelAlignPosition(GetPixelAnchoredPosition(surfaceSize), surfaceSize);
	SetPosition(vec2(alignedPixelPosition.x / surfaceSize.x, alignedPixelPosition.y / surfaceSize.y));
}

vec2 Transform2D::GetPixelAnchoredPosition(const vec2& surfaceSize) const
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

vec2 Transform2D::GetPixelAlignPosition(const vec2& position, const vec2& surfaceSize) const
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

vec2 Transform2D::GetPixelScale(const vec2& surfaceSize) const
{
	return vec2(GetScale().x * surfaceSize.x, GetScale().y * surfaceSize.y);
}
#pragma endregion

#pragma region Public Setters
void Transform2D::SetPixelScale(const vec2& pixelScaleFactor)
{
	this->pixelScaleFactor = pixelScaleFactor;
	SetTransform(surfaceSize, targetSurfaceSize);
}

void Transform2D::SetPixelScale(float pixelScaleFactor)
{
	this->pixelScaleFactor = vec2(pixelScaleFactor, pixelScaleFactor);
	SetTransform(surfaceSize, targetSurfaceSize);
}

void Transform2D::SetPixelPosition(const vec2& pixelPosition)
{
	this->pixelPosition = pixelPosition;
	SetTransform(surfaceSize, targetSurfaceSize);
}

void Transform2D::SetScreenAnchorPoint(AnchorPosition anchorPoint)
{
	this->anchorPosition = anchorPoint;
	SetTransform(surfaceSize, targetSurfaceSize);
}

void Transform2D::SetTextAlignment(AnchorPosition alignPosition)
{
	this->alignPosition = alignPosition;
	SetTransform(surfaceSize, targetSurfaceSize);
}
#pragma endregion

json Transform2D::GetJson() const
{
	json j = Component::GetJson();

	j["ScreenAnchorPoint"] = anchorPosition;
	j["TextAlignment"] = alignPosition;
	j["PixelPosition"] = json { pixelPosition.x, pixelPosition.y };
	j["PixelScale"] = json { pixelScaleFactor.x, pixelScaleFactor.y };

	return j;
}

void Transform2D::SetFromJson(const json& j)
{
	Component::SetFromJson(j);

	SetScreenAnchorPoint((AnchorPosition)j["ScreenAnchorPoint"].get<int>());
	SetTextAlignment((AnchorPosition)j["TextAlignment"].get<int>());
	SetPixelPosition(vec2(j["PixelPosition"][0], j["PixelPosition"][1]));
	SetPixelScale(vec2(j["PixelScale"][0], j["PixelScale"][1]));
}
