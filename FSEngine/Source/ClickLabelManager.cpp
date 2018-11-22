#include "../Header/ClickLabelManager.h"

void ClickLabelManager::Start()
{
	GetParameterCollection()->SetParameter(DoDraw, false);
}

void ClickLabelManager::SceneLoaded()
{
	// note: this will not work for GameObjects added to the scene at runtime!! (unless the scene reloads)
	// TODO: make this work for GameObjects added at runtime
	for (const auto gameObject : gameObjectContainer->GetGameObjects())
		CreateClickLabelForGameObject(gameObject);
}

void ClickLabelManager::CreateClickLabelForGameObject(IGameObject* gameObject)
{
	Transform* gameObjectTransform = gameObject->TryGetComponent<Transform>();
	if (gameObjectTransform == nullptr || gameObjectTransform->GetComponentTypeId() != Types::Transform)
		return;

	IGameObject* clickLabel = gameObjectContainer->AddGameObject(gameObject->GetName() + " - Label", make_unique<ClickLabel>());
	static_cast<ClickLabel*>(clickLabel)->InitializeClickLabel(gameObject);

	Transform* transform = clickLabel->GetComponent<Transform>();
	const float UpOffset = 0.5f;
	transform->SetPosition(gameObjectTransform->GetPosition() + (FSMath::Up * UpOffset));
}

string ClickLabelManager::GetGameObjectType() const
{
	return "ClickLabelManager";
}
