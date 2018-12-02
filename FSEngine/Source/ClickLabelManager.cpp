#include "../Header/ClickLabelManager.h"

ClickLabelManager::ClickLabelManager(Scene* scene, Systems* systems)
 : scene(scene), systems(systems)
{
	systems->eventSystem->AddListener("GameObjectAdded", this);
	systems->eventSystem->AddListener("GameObjectRemoved", this);
}

void ClickLabelManager::InitializeClickLabels()
{
	activeClickLabel = nullptr;
	RemoveAllClickLabels();

	for (const auto gameObject : scene->GetGameObjectContainer()->GetGameObjects())
		CreateClickLabelForGameObject(gameObject);
}

void ClickLabelManager::RemoveAllClickLabels()
{
	for (const auto gameObject : scene->GetGameObjectContainer()->GetGameObjects())
	{
		if (GameObjectNameIsClickLabel(gameObject->GetName()))
			scene->GetGameObjectContainer()->RemoveGameObject(gameObject->GetName());
	}

	clickLabels.clear();
}

void ClickLabelManager::CreateClickLabelForGameObject(IGameObject* gameObject)
{
	if (!ShouldCreateClickLabel(gameObject))
		return;

	auto clickLabel = static_cast<ClickLabel*>(scene->GetGameObjectContainer()->AddGameObject(gameObject->GetName() + LabelSuffix, make_unique<ClickLabel>()));
	clickLabel->InitializeClickLabel(gameObject);

	clickLabels.push_back(clickLabel);
}

bool ClickLabelManager::ShouldCreateClickLabel(const IGameObject* gameObject) const
{
	Transform* gameObjectTransform = gameObject->TryGetComponent<Transform>();

	return gameObjectTransform != nullptr && gameObjectTransform->GetComponentTypeId() == Types::Transform &&
		!GameObjectNameIsClickLabel(gameObject->GetName()) &&
		scene->GetGameObjectContainer()->TryGetGameObject(gameObject->GetName() + LabelSuffix) == nullptr;
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
	if (key == "GameObjectAdded")
		CreateClickLabelForGameObject(scene->GetGameObjectContainer()->GetGameObject(event.get<string>()));

	if (key == "GameObjectRemoved")
		RemoveClickLabel(event.get<string>());
}

void ClickLabelManager::RemoveClickLabel(const string& gameObjectName)
{
	if (GameObjectNameIsClickLabel(gameObjectName))
		return;

	string clickLabelName = gameObjectName + LabelSuffix;

	auto clickLabelToRemove = scene->GetGameObjectContainer()->GetGameObject(clickLabelName);
	clickLabels.erase(std::find(clickLabels.begin(), clickLabels.end(), clickLabelToRemove));
	activeClickLabel = nullptr;

	scene->GetGameObjectContainer()->RemoveGameObject(clickLabelName);
}

bool ClickLabelManager::GameObjectNameIsClickLabel(const string& gameObjectName) const
{
	return gameObjectName.find(LabelSuffix) != string::npos;
}

IGameObject* ClickLabelManager::GetActiveGameObject() const
{
	return activeClickLabel == nullptr ? nullptr : activeClickLabel->GetAttachedGameObject();
}

ClickLabelManager::~ClickLabelManager()
{
	systems->eventSystem->RemoveListener(this);
}
