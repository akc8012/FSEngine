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

	IGameObject* attachedGameObject = nullptr;
	Transform* transform = nullptr;
	Camera* camera = nullptr;

	void SetScaleFromSurfaceSize(const vec2& surfaceSize);
	quat GetCameraLookAtOrientation() const;

	corners GetQuadCorners() const;
	vec3 GetCursorPlaneIntersectPosition() const;
	vec2 GetProjected2DIntersect(const vec3& cursorPlaneIntersectPosition, const corners& corners) const;
	bool Projected2DIntersectWithinCorners(const vec2& projected2DIntersect, const corners& corners) const;

public:
	void Start() override;
	void Update() override;

	void InitializeClickLabel(IGameObject* attachedGameObject);
	bool CursorIntersectsQuad() const;
	IGameObject* GetAttachedGameObject() const;

	string GetGameObjectType() const override;
};
