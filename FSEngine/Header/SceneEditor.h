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

	vec3 cursorOffset;
	unique_ptr<ClickLabelManager> clickLabelManager;

	void TranslateActiveGameObject(IGameObject* activeGameObject);

public:
	SceneEditor(Scene* scene, Systems* systems);
	void InitializeEditor();

	void Update() override;
};
