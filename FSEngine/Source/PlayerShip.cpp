#include "../Header/PlayerShip.h"

PlayerShip::PlayerShip()
 : Model("C:/Model/Arwing/arwing.dae")
{

}

void PlayerShip::Start()
{
	transform = GetComponent<TransformComponent>();
	camera = dynamic_cast<Camera*>(gameObjectContainer->GetGameObject("Camera"));

	transform->SetScale(vec3(0.025f, 0.025f, 0.025f));
	transform->SetRotation(glm::radians(180.f), vec3(0, 1, 0));
}

void PlayerShip::Update(float deltaTime)
{
	if (!fileSystem->GetSettingsValue<bool>("ShipControl"))
		return;

	vec3 inputVector = vec3(input->GetHorizontalAxis(), 0, input->GetVerticalAxis());
	if (glm::length(inputVector) != 0)
		inputVector = glm::normalize(inputVector);

	const float Speed = 3;
	transform->Translate(inputVector * deltaTime * Speed);

	camera->SetPosition(transform->GetPosition() + vec3(0, 0, fileSystem->GetSettingsValue<float>("CameraDistance")));
}
