#include "../Header/SceneEditor.h"

SceneEditor::SceneEditor(Scene* scene, Systems* systems)
 : scene(scene), systems(systems)
{
	clickLabelManager = make_unique<ClickLabelManager>(scene, systems);
	systems->eventSystem->AddListener("UndoKeyPressed", this);

	InitializeEditor();
}

void SceneEditor::InitializeEditor()
{
	UpdateEditorMode();

	clickLabelManager->InitializeClickLabels();

	camera = scene->GetGameObjectContainer()->GetGameObjectAs<Camera>("Camera");
	gameObjectTranslator = make_unique<GameObjectTranslator>(systems->input.get(), camera);

	ClearActionHistory();
}

void SceneEditor::UpdateEditorMode()
{
	bool editorModeSetting = systems->fileSystem->GetSettingsValue<bool>("EditorMode");
	if (editorMode && !editorModeSetting)
		systems->eventSystem->SendEvent("EditorModeDisabled", nullptr, false);
	else if (!editorMode && editorModeSetting)
		systems->eventSystem->SendEvent("EditorModeEnabled", nullptr, false);

	editorMode = editorModeSetting;
}

void SceneEditor::ClearActionHistory()
{
	while (!actionHistory.empty())
		actionHistory.pop();
}

void SceneEditor::Update()
{
	UpdateEditorMode();
	if (!editorMode)
		return;

	clickLabelManager->Update();

	auto activeGameObject = clickLabelManager->GetActiveGameObject();
	if (activeGameObject != nullptr)
		UpdateActiveGameObject(activeGameObject);
}

void SceneEditor::UpdateActiveGameObject(IGameObject* activeGameObject)
{
	if (gameObjectTranslator->ShouldStartTranslate())
		gameObjectTranslator->SetGameObject(activeGameObject);

	if (gameObjectTranslator->ShouldTranslate())
		gameObjectTranslator->TranslateGameObject();

	if (gameObjectTranslator->ShouldEndTranslate())
	{
		actionHistory.push(gameObjectTranslator->GetHistoryAction());
		gameObjectTranslator->SetGameObject(nullptr);
	}

	if (systems->input->IsButtonPressed(SDL_SCANCODE_DELETE))
	{
		actionHistory.push(CreateDeleteAction(activeGameObject));
		scene->GetGameObjectContainer()->RemoveGameObject(activeGameObject->GetName());
	}
}

json SceneEditor::CreateDeleteAction(const IGameObject* activeGameObject) const
{
	json action;
	action["ActionType"] = "Delete";
	action["GameObject"] = activeGameObject->GetName();
	action["GameObjectJson"] = activeGameObject->GetJson();

	return action;
}

void SceneEditor::ReceiveEvent(const string& key, const json& event)
{
	if (key == "UndoKeyPressed" && editorMode && actionHistory.size() > 0)
		DoUndoAction();
}

void SceneEditor::DoUndoAction()
{
	json action = actionHistory.top();
	actionHistory.pop();

	string gameObjectName = action["GameObject"].get<string>();

	if (action["ActionType"] == "Delete")
		scene->LoadGameObjectFromJson(gameObjectName, action["GameObjectJson"]);
	else
	{
		auto gameObject = scene->GetGameObjectContainer()->GetGameObject(gameObjectName);
		// TODO: checks here for other action types
		gameObjectTranslator->DoUndoAction(action, gameObject);
	}
}

SceneEditor::~SceneEditor()
{
	systems->eventSystem->RemoveListener(this);
}
