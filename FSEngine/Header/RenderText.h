#pragma once
#include "GameObject.h"

using std::vector;
using std::string;

class RenderText : public GameObject
{
public:
	enum AnchorPosition { Center, TopLeft, TopRight, BottomLeft, BottomRight };

private:
	AnchorPosition anchorPosition = Center;
	AnchorPosition alignPosition = Center;
	vec2 pixelPosition = vec2(0, 0);
	vec2 pixelScaleFactor = vec2(1, 1);

	vec2 surfaceSize;

	void SetTransformFromSurfaceSize(const vec2& surfaceSize);
	void SetScaleFromSurfaceSize(const vec2& surfaceSize);
	void SetPositionFromSurfaceSize(const vec2& surfaceSize);

	vec2 CalculateAspectRatio(const vec2& surfaceSize) const;
	vec2 GetPixelAnchoredPosition(const vec2& surfaceSize) const;
	vec2 GetPixelAlignPosition(const vec2& position, const vec2& surfaceSize) const;
	vec2 GetPixelScale(const vec2& surfaceSize) const;

public:
	void Start() override;
	void Update() override;
	void ReceiveEvent(const string& key, const json& event) override;

	void SetText(const string& text);

	void SetPixelScale(const vec2& pixelScaleFactor);
	void SetPixelScale(float pixelScaleFactor);
	void SetPixelPosition(const vec2& pixelPosition);
	void SetScreenAnchorPoint(AnchorPosition anchorPoint);
	void SetTextAlignment(AnchorPosition alignPosition);

	json GetJson() const override;
	void SetFromJson(const json& j) override;

	string GetGameObjectType() const override;
};
