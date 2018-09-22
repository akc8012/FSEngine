#include "../Header/PlayerShip.h"

PlayerShip::PlayerShip()
 : Model("C:/Model/Arwing/arwing.dae")
{

}

void PlayerShip::Start()
{
	transform = GetComponent<TransformComponent>().get();
	camera = gameObjectContainer->GetGameObjectAs<Camera>("Camera");

	ResetValues();
}

void PlayerShip::ResetValues()
{
	transform->SetPosition(vec3(0, 0, 0));
	transform->SetScale(vec3(0.025f, 0.025f, 0.025f));
	transform->SetOrientation(vec3(0, 0, 180));

	direction = vec3(0, 0, 180);
}

void PlayerShip::Update()
{
	if (systems->fileSystem->GetSettingsValue<bool>("ShipControl"))
	{
		if (systems->input->IsButtonPressed(SDL_SCANCODE_P))
			ResetValues();

		ControlShip();
		//SetCamera();
	}
}

void PlayerShip::ControlShip()
{
	vec3 input(systems->input->GetVerticalAxis(), 0, -systems->input->GetHorizontalAxis());
	direction += glm::degrees(input) * GetFrameAdjustedSpeed();

<<<<<<< HEAD
	transform->SetOrientation(direction);
=======
	transform->SetRotation(direction);
>>>>>>> b0294f1b90ae4641a98cf919d8937d817ca3fa8f
}

void PlayerShip::SetCamera()
{
	const float CameraDistance = 6;
	camera->SetPosition(transform->GetPosition() + (-FSMath::Forward * CameraDistance));
}

float PlayerShip::GetFrameAdjustedSpeed() const
{
	return systems->fileSystem->GetSettingsValue<float>("ShipSpeed") * systems->gameTimer->GetDeltaTime();
}
