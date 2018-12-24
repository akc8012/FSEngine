#include "../Header/PlayerShip.h"

void MyFunction()
{
	printFS("my function");
}

template <typename T>
T MyAdd(T a, T b)
{
	return a + b;
}

PlayerShip::PlayerShip()
{
	AddComponent(make_shared<Model>("C:/Model/Arwing/arwing.dae"));
	transform = AddComponent(make_shared<Transform>());
}

void PlayerShip::Start()
{
	ResetValues();
}

void PlayerShip::SceneLoaded()
{
	lua.open_libraries(sol::lib::base);
	lua.script_file("Resource/Script/script1.lua");
	lua.script_file("Resource/Script/script2.lua");

	lua.new_usertype<vec3>("vec3",
		sol::constructors<vec3(), vec3(float, float, float)>(),
		"x", &vec3::x,
		"y", &vec3::y,
		"z", &vec3::z,

		sol::meta_function::addition,    sol::resolve<vec3(const vec3&, const vec3&)>(glm::operator+<float, glm::packed_highp>),
		sol::meta_function::subtraction, sol::resolve<vec3(const vec3&, const vec3&)>(glm::operator-<float, glm::packed_highp>)
	);
	// TODO: vec4 and vec2

	lua.new_usertype<Transform>("transform",
		"position", sol::property(&Transform::GetPosition, sol::resolve<void(const vec3&)>(&Transform::SetPosition)),
		"scale",    sol::property(&Transform::GetScale,    sol::resolve<void(const vec3&)>(&Transform::SetScale))
	);

	transform->SetPosition(5, 4, 3);
	lua["playerTransform"] = transform;

	lua["run"]();
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
