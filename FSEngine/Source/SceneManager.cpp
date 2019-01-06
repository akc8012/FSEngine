#include "../Header/SceneManager.h"

SceneManager::SceneManager(Systems* systems)
 : systems(systems)
{
	currentScene = make_unique<Scene>("scene", systems);
	sceneEditor = make_unique<SceneEditor>(currentScene.get(), systems);

	systems->eventSystem->AddListener("SaveKeyPressed", this);
	systems->eventSystem->AddListener("LoadKeyPressed", this);
	systems->eventSystem->AddListener("GameStopped", this);
	systems->eventSystem->AddListener("WindowFocusGained", this);
	systems->eventSystem->AddListener("WindowFocusLost", this);
}

void SceneManager::ReceiveEvent(const string& key, const json& event)
{
	if (key == "SaveKeyPressed" || key == "GameStopped" ||
		(key == "WindowFocusLost" && systems->fileSystem->GetSettingsValue<bool>("LoadSceneOnFocus")))
		currentScene->SaveScene();

	if (key == "LoadKeyPressed" || (key == "WindowFocusGained" && systems->fileSystem->GetSettingsValue<bool>("LoadSceneOnFocus")))
	{
		currentScene->LoadScene();
		sceneEditor->InitializeEditor();
	}
}

void SceneManager::Update()
{
	sceneEditor->Update();

	UpdateGameObjects(false);
	UpdateGameObjects(true);
}

void SceneManager::UpdateGameObjects(bool doLateUpdate)
{
	for (auto gameObject : currentScene->GetGameObjectContainer()->GetGameObjects())
	{
		if (gameObject->GetParameterCollection()->GetParameter(GameObject::DoUpdate) && gameObject->GetParameterCollection()->GetParameter(GameObject::DoLateUpdate) == doLateUpdate)
			gameObject->Update();
	}
}

void SceneManager::Draw(Renderer* renderer)
{
	DrawGameObjects(renderer, false);
	DrawGameObjects(renderer, true);

	DrawImGuiGameObjectsWindow();
}

void SceneManager::DrawGameObjects(Renderer* renderer, bool doLateDraw)
{
	for (auto gameObject : currentScene->GetGameObjectContainer()->GetGameObjects())
	{
		if (gameObject->GetParameterCollection()->GetParameter(GameObject::DoDraw) && gameObject->GetParameterCollection()->GetParameter(GameObject::DoLateDraw) == doLateDraw)
			renderer->RenderGameObject(gameObject);
	}
}

void SceneManager::DrawImGuiGameObjectsWindow() const
{
	const int ListBoxHeight = 20;
	const int ListBoxFullSizeWidth = -1;

	static int currentItemIndex = 0;
	auto nameList = GetGameObjectNameList();

	ImGui::Begin("GameObjects", NULL, ImGuiWindowFlags_None);

		ImGui::PushItemWidth(ListBoxFullSizeWidth);
		ImGui::ListBox("##GameObjects", &currentItemIndex, nameList.data(), (int)nameList.size(), ListBoxHeight);
		ImGui::PopItemWidth();

	ImGui::End();
}

vector<const char*> SceneManager::GetGameObjectNameList() const
{
	vector<const char*> nameList;
	for (const auto gameObject : currentScene->GetGameObjectContainer()->GetGameObjects())
		nameList.push_back(gameObject->GetName().c_str());

	return nameList;
}

Scene* SceneManager::GetCurrentScene() const
{
	return currentScene.get();
}

SceneManager::~SceneManager()
{
	systems->eventSystem->RemoveListener(this);
}
