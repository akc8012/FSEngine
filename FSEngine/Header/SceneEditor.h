#pragma once
#include "Scene.h"
#include "ClickLabelManager.h"

class SceneEditor
{
private:
	Scene* scene = nullptr;
	unique_ptr<ClickLabelManager> clickLabelManager;

public:
	SceneEditor(Scene* scene, Systems* systems);
	void InitializeEditor();

	void Update();
};
