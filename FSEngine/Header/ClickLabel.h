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

	const vec3 DeselectedColor = vec3(0.2f, 0.2f, 0.7f);
	const vec3 SelectedColor = vec3(0.7f, 0.7f, 0.2f);

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
	~ClickLabel();

	void Start() override;
	void Update() override;
	void ReceiveEvent(const string& key, const json& event) override;

	void InitializeClickLabel(IGameObject* attachedGameObject);
	bool CursorIntersectsQuad() const;
	IGameObject* GetAttachedGameObject() const;

	void Select();
	void Deselect();

	string GetGameObjectType() const override;
};
