#pragma once
#include "IUpdatable.h"
#include "Scene.h"
#include "Camera.h"
#include "ClickLabelManager.h"
#include "EditorAction.h"

#include <stack>
using std::stack;

class SceneEditor : public IUpdatable
{
private:
	Scene* scene = nullptr;
	Systems* systems = nullptr;
	Camera* camera = nullptr;

	stack<json> actionHistory;

	bool editorMode;
	vec3 cursorOffset;
	vec3 originalPosition;
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
