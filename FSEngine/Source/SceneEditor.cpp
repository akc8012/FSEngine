#include "../Header/SceneEditor.h"

SceneEditor::SceneEditor(Scene* scene, Systems* systems)
 : scene(scene), systems(systems)
{
	clickLabelManager = make_unique<ClickLabelManager>(scene, systems);
	InitializeEditor();
}

void SceneEditor::InitializeEditor()
{
	UpdateEditorMode();

	clickLabelManager->CreateClickLabels();

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

	{
		if (systems->input->IsButtonHeld(SDL_SCANCODE_LCTRL) && systems->input->IsButtonPressed(SDL_SCANCODE_Z) &&
			actionHistory.size() > 0)
		{
			json action = actionHistory.top();
			actionHistory.pop();

			auto affectedGameObject = scene->GetGameObjectContainer()->GetGameObject(action["AffectedGameObject"].get<string>());
			vec3 moveDelta = vec3(action["MoveDelta"][0], action["MoveDelta"][1], action["MoveDelta"][2]);
			affectedGameObject->GetComponent<Transform>()->Translate(-moveDelta);
		}
	}


	{
		clickLabelManager->Update();
		auto activeGameObject = clickLabelManager->GetActiveGameObject();
		if (activeGameObject == nullptr)
			return;

		if (gameObjectTranslator->ShouldStartTranslate())
			gameObjectTranslator->SetGameObject(activeGameObject);

		if (gameObjectTranslator->ShouldTranslate())
			gameObjectTranslator->TranslateGameObject();

		if (gameObjectTranslator->ShouldEndTranslate())
			actionHistory.push(gameObjectTranslator->GetHistoryAction());
	}
}
