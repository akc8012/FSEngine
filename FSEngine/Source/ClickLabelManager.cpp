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

void ClickLabelManager::CreateClickLabelForGameObject(const IGameObject* gameObject)
{
	Transform* gameObjectTransform = gameObject->TryGetComponent<Transform>();
	if (gameObjectTransform == nullptr || gameObjectTransform->GetComponentTypeId() != Types::Transform)
		return;

	IGameObject* clickLabel = gameObjectContainer->AddGameObject(gameObject->GetName() + " - Label", make_unique<ClickLabel>());
	static_cast<ClickLabel*>(clickLabel)->InitializeClickLabel(gameObject->GetName());

	Transform* transform = clickLabel->GetComponent<Transform>();
	transform->SetPosition(gameObjectTransform->GetPosition() + (FSMath::Up * 0.5f));
	transform->SetScale(vec3(1.f, 0.25f, 1.f));
}

string ClickLabelManager::GetGameObjectType() const
{
	return "ClickLabelManager";
}
