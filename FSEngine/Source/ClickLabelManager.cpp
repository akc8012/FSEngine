#include "../Header/ClickLabelManager.h"

ClickLabelManager::ClickLabelManager(Scene* scene, Systems* systems)
 : scene(scene), systems(systems)
{
	systems->eventSystem->AddListener("GameObjectRemoved", this);
}

// note: this will not work for GameObjects added to the scene at runtime!! (unless the scene reloads)
// TODO: make this work for GameObjects added at runtime
void ClickLabelManager::CreateClickLabels()
{
	activeClickLabel = nullptr;
	clickLabels.clear();

	for (const auto gameObject : scene->GetGameObjectContainer()->GetGameObjects())
	{
		auto clickLabel = CreateClickLabelForGameObject(gameObject);
		if (clickLabel != nullptr)
			clickLabels.push_back(clickLabel);
	}
}

ClickLabel* ClickLabelManager::CreateClickLabelForGameObject(IGameObject* gameObject)
{
	Transform* gameObjectTransform = gameObject->TryGetComponent<Transform>();
	if (gameObjectTransform == nullptr || gameObjectTransform->GetComponentTypeId() != Types::Transform)
		return nullptr;

	auto clickLabel = static_cast<ClickLabel*>(scene->GetGameObjectContainer()->AddGameObject(gameObject->GetName() + LabelSuffix, make_unique<ClickLabel>()));
	clickLabel->InitializeClickLabel(gameObject);

	return clickLabel;
}

void ClickLabelManager::Update()
{
	if (systems->input->IsButtonPressed(SDL_BUTTON_LEFT))
	{
		if (activeClickLabel != nullptr)
			activeClickLabel->Deselect();

		activeClickLabel = GetCursorIntersectingClickLabel();

		if (activeClickLabel != nullptr)
			activeClickLabel->Select();
	}
}

ClickLabel* ClickLabelManager::GetCursorIntersectingClickLabel() const
{
	for (const auto clickLabel : clickLabels)
	{
		if (clickLabel->CursorIntersectsQuad())
			return clickLabel;
	}

	return nullptr;
}

void ClickLabelManager::ReceiveEvent(const string& key, const json& event)
{
	if (key == "GameObjectRemoved")
		RemoveClickLabel(event.get<string>());
}

void ClickLabelManager::RemoveClickLabel(const string& gameObjectName)
{
	if (gameObjectName.find(LabelSuffix) != string::npos)
		return;

	string clickLabelName = gameObjectName + LabelSuffix;

	auto clickLabelToRemove = scene->GetGameObjectContainer()->GetGameObject(clickLabelName);
	clickLabels.erase(std::find(clickLabels.begin(), clickLabels.end(), clickLabelToRemove));
	activeClickLabel = nullptr;

	scene->GetGameObjectContainer()->RemoveGameObject(clickLabelName);
}

IGameObject* ClickLabelManager::GetActiveGameObject() const
{
	return activeClickLabel == nullptr ? nullptr : activeClickLabel->GetAttachedGameObject();
}

ClickLabelManager::~ClickLabelManager()
{
	systems->eventSystem->RemoveListener(this);
}
