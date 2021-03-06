#include "../Header/PlayerShip.h"

PlayerShip::PlayerShip()
{
	AddComponent(make_shared<Model>("C:/Model/Arwing/arwing.dae"));
	transform = AddComponent(make_shared<Transform>());
}

void PlayerShip::Start()
{
	ResetValues();
}

void PlayerShip::ResetValues()
{
	transform->SetPosition(FSMath::Zero);
	transform->SetScale(vec3(0.025f, 0.025f, 0.025f));
	transform->SetOrientation(vec3(0, 180, 0));

	direction = vec3(0, 0, 180);
}

ComponentCollection<Mesh>* PlayerShip::GetMeshCollection() const
{
	return GetComponent<Model>()->GetMeshCollection();
}

ComponentCollection<Texture>* PlayerShip::GetTextureCollection() const
{
	return GetComponent<Model>()->GetTextureCollection();
}

void PlayerShip::Update()
{
	if (!systems->fileSystem->GetSettingsValue<bool>("EditorMode"))
	{
		if (systems->input->IsButtonPressed(SDL_SCANCODE_P))
			ResetValues();

		//ControlShip();
		//SetCamera();
	}
}

void PlayerShip::ControlShip()
{
	vec3 input(systems->input->GetVerticalAxis(), 0, -systems->input->GetHorizontalAxis());
	direction += glm::degrees(input) * GetFrameAdjustedSpeed();

	transform->SetOrientation(direction);

	if (!systems->input->IsButtonHeld(SDL_SCANCODE_SPACE))
		transform->Translate(-transform->GetForward() * GetFrameAdjustedSpeed());
}

void PlayerShip::SetCamera()
{
	const float CameraDistance = 6;
	vec3 cameraPosition = transform->GetPosition() + (-FSMath::Forward * CameraDistance);

	auto event = json { cameraPosition.x, cameraPosition.y, cameraPosition.z };
	systems->eventSystem->SendEvent("CameraPosition", event);
}

float PlayerShip::GetFrameAdjustedSpeed() const
{
	return systems->fileSystem->GetSettingsValue<float>("ShipSpeed") * systems->gameTimer->GetDeltaTime();
}

string PlayerShip::GetGameObjectType() const
{
	return "PlayerShip";
}
