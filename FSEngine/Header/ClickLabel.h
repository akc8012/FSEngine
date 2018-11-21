#pragma once
#include "GameObject.h"
#include "Camera.h"

class ClickLabel : public GameObject
{
private:
	struct corners
	{
		vec3 topLeft, topRight, bottomLeft;
	};

	Transform* transform = nullptr;
	Camera* camera = nullptr;

	quat GetCameraLookAtOrientation() const;

	bool CursorIntersectsQuad() const;
	corners GetQuadCorners() const;
	vec3 GetCursorPlaneIntersectPosition() const;
	vec2 GetProjected2DIntersect(const vec3& cursorPlaneIntersectPosition, const corners& corners) const;
	bool Projected2DIntersectWithinCorners(const vec2& projected2DIntersect, const corners& corners) const;

public:
	void Start() override;
	void Update() override;

	void InitializeClickLabel(const string& gameObjectName);

	string GetGameObjectType() const override;
};
