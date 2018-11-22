#include "../Header/ClickLabelManager.h"

void ClickLabelManager::Start()
{
	GetParameterCollection()->SetParameter(DoDraw, false);
}

void ClickLabelManager::SceneLoaded()
{
	clickLabels.clear();

	// note: this will not work for GameObjects added to the scene at runtime!! (unless the scene reloads)
	// TODO: make this work for GameObjects added at runtime
	for (const auto gameObject : gameObjectContainer->GetGameObjects())
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

	auto clickLabel = static_cast<ClickLabel*>(gameObjectContainer->AddGameObject(gameObject->GetName() + " - Label", make_unique<ClickLabel>()));
	clickLabel->InitializeClickLabel(gameObject);

	Transform* transform = clickLabel->GetComponent<Transform>();
	const float UpOffset = 0.5f;
	transform->SetPosition(gameObjectTransform->GetPosition() + (FSMath::Up * UpOffset));

	return clickLabel;
}

void ClickLabelManager::Update()
{
	if (systems->input->IsButtonPressed(SDL_BUTTON_LEFT))
		activeClickLabel = GetCursorIntersectingClickLabel();
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

string ClickLabelManager::GetGameObjectType() const
{
	return "ClickLabelManager";
}
