#include "../Header/PlayerShip.h"

PlayerShip::PlayerShip()
 : Model("C:/Model/Arwing/arwing.dae")
{

}

void PlayerShip::Start()
{
	transform = GetComponent<TransformComponent>();

	transform->SetScale(vec3(0.025f, 0.025f, 0.025f));
	transform->Rotate(glm::radians(180.f), vec3(0, 1, 0));
}

void PlayerShip::Update(float deltaTime)
{
	vec3 inputVector = vec3(input->GetHorizontalAxis(), 0, input->GetVerticalAxis());
	transform->Translate(-inputVector);
}
