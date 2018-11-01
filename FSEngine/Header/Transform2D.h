#pragma once
#include "Transform.h"

class Transform2D : public Transform
{
public:
	enum AnchorPosition { Center, TopLeft, TopRight, BottomLeft, BottomRight };

private:
	AnchorPosition anchorPosition = Center;
	AnchorPosition alignPosition = Center;
	vec2 pixelPosition = vec2(0, 0);
	vec2 pixelScaleFactor = vec2(1, 1);

	vec2 surfaceSize;
	vec2 targetSurfaceSize;

	void SetScaleFromSurfaceSize(const vec2& surfaceSize, const vec2& aspectRatio);
	void SetPositionFromSurfaceSize(const vec2& surfaceSize);

	vec2 CalculateAspectRatio(const vec2& surfaceSize) const;
	vec2 GetPixelAnchoredPosition(const vec2& surfaceSize) const;
	vec2 GetPixelAlignPosition(const vec2& position, const vec2& surfaceSize) const;
	vec2 GetPixelScale(const vec2& surfaceSize) const;

public:
	static const Types::ComponentType ComponentTypeId = Types::Transform2D;
	Types::ComponentType GetComponentTypeId() const override;

	void SetTransform(const vec2& surfaceSize, const vec2& targetSurfaceSize);

	void SetPixelScale(const vec2& pixelScaleFactor);
	void SetPixelScale(float pixelScaleFactor);
	void SetPixelPosition(const vec2& pixelPosition);
	void SetScreenAnchorPoint(AnchorPosition anchorPoint);
	void SetTextAlignment(AnchorPosition alignPosition);
};
