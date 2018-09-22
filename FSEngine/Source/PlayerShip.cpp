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
	transform->SetPosition(vec3(0, 0, 4));
	transform->SetScale(vec3(0.025f, 0.025f, 0.025f));
	transform->SetOrientation(vec3(0, 0, 180));

	direction = vec3(0, 0, 180);
}

void PlayerShip::Update()
{
	if (!systems->fileSystem->GetSettingsValue<bool>("EditorMode"))
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

	transform->SetOrientation(direction);

	if (!systems->input->IsButtonHeld(SDL_SCANCODE_SPACE))
	{
		vec3 forward = transform->GetOrientation() * -FSMath::Forward;
		transform->Translate(forward * GetFrameAdjustedSpeed());
	}
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
