#pragma once
#include "IUpdatable.h"
#include "Scene.h"
#include "Camera.h"
#include "ClickLabelManager.h"
#include "EditorAction.h"
#include "GameObjectTranslator.h"
#include "IEventListener.h"

#include <stack>
using std::stack;

class SceneEditor : public IUpdatable, public IEventListener
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

	void UpdateActiveGameObject(IGameObject* activeGameObject);

	void DoUndoAction();

public:
	SceneEditor(Scene* scene, Systems* systems);
	~SceneEditor();

	void InitializeEditor();

	void Update() override;
	void ReceiveEvent(const string& key, const json& event) override;
};
