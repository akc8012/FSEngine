#pragma once
#include "IUpdatable.h"
#include "Scene.h"
#include "ClickLabelManager.h"

class SceneEditor : public IUpdatable
{
private:
	Scene* scene = nullptr;
	unique_ptr<ClickLabelManager> clickLabelManager;

public:
	SceneEditor(Scene* scene, Systems* systems);
	void InitializeEditor();

	void Update() override;
};
