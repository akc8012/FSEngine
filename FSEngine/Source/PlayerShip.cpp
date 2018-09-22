#include "../Header/PlayerShip.h"

PlayerShip::PlayerShip()
 : Model("C:/Model/Arwing/arwing.dae")
{

}

void PlayerShip::Start()
{
	transform = GetComponent<TransformComponent>().get();
	camera = gameObjectContainer->GetGameObjectAs<Camera>("Camera");

	transform->SetScale(vec3(0.025f, 0.025f, 0.025f));
	transform->SetOrientation(glm::radians(180.f), vec3(0, 1, 0));
}

void PlayerShip::Update()
{
	if (systems->fileSystem->GetSettingsValue<bool>("ShipControl"))
	{
		vec3 inputVector = vec3(systems->input->GetHorizontalAxis(), 0, systems->input->GetVerticalAxis());
		if (glm::length(inputVector) != 0)
			inputVector = glm::normalize(inputVector);

		float shipSpeed = systems->fileSystem->GetSettingsValue<float>("ShipSpeed");
		transform->Translate(inputVector * systems->gameTimer->GetDeltaTime() * shipSpeed);

		//camera->SetPosition(transform->GetPosition() + vec3(0, 0, systems->fileSystem->GetSettingsValue<float>("CameraDistance")));
	}
}
