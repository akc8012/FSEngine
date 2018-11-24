#pragma once
#include "IUpdatable.h"
#include "Scene.h"
#include "Camera.h"
#include "ClickLabelManager.h"

class SceneEditor : public IUpdatable
{
private:
	Scene* scene = nullptr;
	Systems* systems = nullptr;
	Camera* camera = nullptr;

	bool editorMode;
	vec3 cursorOffset;
	unique_ptr<ClickLabelManager> clickLabelManager;

	void UpdateEditorMode();

	void TranslateActiveGameObject(IGameObject* activeGameObject);

	plane GetFloorPlane(const vec3& objectPosition) const;
	plane GetVerticalPlane(const vec3& objectPosition) const;

	vec3 CalculatePositionAlongPlane(const plane& plane) const;
	vec3 CalculateVerticalPositionAlongPlane(const plane& plane) const;
	bool ShouldResetCursorOffset() const;

public:
	SceneEditor(Scene* scene, Systems* systems);
	void InitializeEditor();

	void Update() override;
};
