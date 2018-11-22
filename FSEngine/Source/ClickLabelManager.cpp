#include "../Header/ClickLabelManager.h"

ClickLabelManager::ClickLabelManager(Scene* scene, Systems* systems)
 : scene(scene), systems(systems)
{

}

void ClickLabelManager::CreateClickLabels()
{
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

	auto clickLabel = static_cast<ClickLabel*>(scene->GetGameObjectContainer()->AddGameObject(gameObject->GetName() + " - Label", make_unique<ClickLabel>()));
	clickLabel->InitializeClickLabel(gameObject);

	Transform* transform = clickLabel->GetComponent<Transform>();
	const float UpOffset = 0.5f;
	transform->SetPosition(gameObjectTransform->GetPosition() + (FSMath::Up * UpOffset));

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

IGameObject * ClickLabelManager::GetActiveGameObject() const
{
	return activeClickLabel == nullptr ? nullptr : activeClickLabel->GetAttachedGameObject();
}
