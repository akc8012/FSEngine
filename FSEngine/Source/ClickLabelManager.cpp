#include "../Header/ClickLabelManager.h"

void ClickLabelManager::Start()
{
	GetParameterCollection()->SetParameter(DoDraw, false);
}

void ClickLabelManager::SceneLoaded()
{
	for (const auto gameObject : gameObjectContainer->GetGameObjects())
	{
		if (gameObject->TryGetComponent<Transform>() == nullptr)
			continue;

		auto clickLabel = gameObjectContainer->AddGameObject(gameObject->GetName() + "Label", make_unique<ClickLabel>());
		clickLabel->SetSerializable(false);
		clickLabel->AddComponent(make_shared<Color>(vec3(0.2f, 0.2f, 0.5f)), "Shading");
		clickLabel->GetComponent<Transform>()->SetPosition(gameObject->GetComponent<Transform>()->GetPosition() + FSMath::Up);

		clickLabel->SceneLoaded();
	}

	printFS("click label manager loaded");
}

string ClickLabelManager::GetGameObjectType() const
{
	return "ClickLabelManager";
}
