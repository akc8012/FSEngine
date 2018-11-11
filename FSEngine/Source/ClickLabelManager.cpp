#include "../Header/ClickLabelManager.h"

void ClickLabelManager::Start()
{
	GetParameterCollection()->SetParameter(DoDraw, false);
}

void ClickLabelManager::SceneLoaded()
{
	for (const auto gameObject : gameObjectContainer->GetGameObjects())
	{
		auto gameObjectTransform = gameObject->TryGetComponent<Transform>();
		if (gameObjectTransform == nullptr || gameObjectTransform->GetComponentTypeId() != Types::Transform)
			continue;

		auto clickLabel = gameObjectContainer->AddGameObject(gameObject->GetName() + " - Label", make_unique<ClickLabel>());
		clickLabel->SceneLoaded(); // TODO: make this less bad

		auto transform = clickLabel->GetComponent<Transform>();
		transform->SetPosition(gameObjectTransform->GetPosition() + (FSMath::Up * 0.5f));
		transform->SetScale(vec3(1.f, 0.25f, 1.f));
	}
}

string ClickLabelManager::GetGameObjectType() const
{
	return "ClickLabelManager";
}
