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

	DrawImGuiGameObjectsWindow();
	clickLabelManager->Update();

	auto activeGameObject = clickLabelManager->GetActiveGameObject();
	if (activeGameObject != nullptr)
		UpdateActiveGameObject(activeGameObject);
}

#pragma region ImGui
void SceneEditor::DrawImGuiGameObjectsWindow() const
{
	ImGui::ShowDemoWindow(NULL);

	static int currentItemIndex = 0;
	auto nameList = GetGameObjectNameList();

	for (auto name : nameList)
		DrawClickBox(name);

	ImGui::Begin("GameObjects", NULL, ImGuiWindowFlags_None);

		const int ListBoxHeight = 20;
		const int FullSizeWidth = -1;
		
		ImGui::PushItemWidth(FullSizeWidth);
		ImGui::ListBox("##GameObjects", &currentItemIndex, nameList.data(), (int)nameList.size(), ListBoxHeight);
		ImGui::PopItemWidth();

	ImGui::End();
}

vector<const char*> SceneEditor::GetGameObjectNameList() const
{
	vector<const char*> nameList;
	for (const auto gameObject : scene->GetGameObjectContainer()->GetGameObjects())
	{
		auto& name = gameObject->GetName();
		if (name.find("- Label") == string::npos) // TEMPORARY
			nameList.push_back(name.c_str());
	}

	return nameList;
}

void SceneEditor::DrawClickBox(const string& name) const
{
	ImGui::Begin(("##" + name).c_str(), NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);

		const int FullSizeWidth = -1;
		ImGui::PushItemWidth(FullSizeWidth);

		auto white = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
		auto yellow = ImVec4(1.0f, 1.0f, 0.0f, 1.0f);

		ImGui::TextColored(ImGui::IsWindowFocused() ? yellow : white, name.c_str());
		ImGui::PopItemWidth();

	ImGui::End();
}
#pragma endregion

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
