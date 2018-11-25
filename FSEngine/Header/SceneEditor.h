#pragma once
#include "IUpdatable.h"
#include "Scene.h"
#include "Camera.h"
#include "ClickLabelManager.h"
#include "EditorAction.h"
#include "GameObjectTranslator.h"

#include <stack>
using std::stack;

class SceneEditor : public IUpdatable
{
private:
	Scene* scene = nullptr;
	Systems* systems = nullptr;
	Camera* camera = nullptr;

	bool editorMode;
	unique_ptr<ClickLabelManager> clickLabelManager;
	unique_ptr<GameObjectTranslator> gameObjectTranslator;
	stack<json> actionHistory;

	void UpdateEditorMode();
	void ClearActionHistory();

public:
	SceneEditor(Scene* scene, Systems* systems);
	void InitializeEditor();

	void Update() override;
};
