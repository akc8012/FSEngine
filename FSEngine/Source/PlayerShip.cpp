#include "../Header/PlayerShip.h"

PlayerShip::PlayerShip()
 : Model("C:/Model/Arwing/arwing.dae")
{

}

void PlayerShip::Start()
{
	transform = GetComponent<TransformComponent>();

	/*transform->SetScale(vec3(0.025f, 0.025f, 0.025f));
	transform->SetRotation(glm::radians(180.f), vec3(0, 1, 0));*/


	transform->SetPosition(vec3(0));

	json shipPosition = fileSystem->GetSettingsValue("ShipPosition");

	if (fileSystem->GetSettingsValue<bool>("DoTranslate"))
		transform->Translate(vec3(shipPosition[0], shipPosition[1], shipPosition[2]));
	else
		transform->SetPosition(vec3(shipPosition[0], shipPosition[1], shipPosition[2]));

	printf("%s\n", TransformComponent::GetFormattedVectorString(transform->GetPosition()).c_str());
}

void PlayerShip::Update(float deltaTime)
{
	//vec3 inputVector = vec3(input->GetHorizontalAxis(), 0, input->GetVerticalAxis());
	//transform->Translate(inputVector);

	//system("CLS");
	//printf("%s", TransformComponent::GetFormattedMatrixString(transform->GetMatrix()).c_str());

	//printf("\n");

	//printf("(%f, %f)", inputVector.x, inputVector.z);
}
