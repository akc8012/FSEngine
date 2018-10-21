#include "../Header/GameObject.h"

GameObject::GameObject()
{
	components = make_unique<ComponentContainer>();

	string parameterNames[] = { "DoUpdate", "DoDraw", "DoLateUpdate", "DoLateDraw" };
	parameterCollection = make_unique<ParameterCollection<Parameters, ParametersLength>>(parameterNames);
	SetDefaultParameters();
}

void GameObject::SetDefaultParameters()
{
	Parameters defaultTrue[] = { DoUpdate, DoDraw };
	Parameters defaultFalse[] = { DoLateUpdate, DoLateDraw };

	for (const auto& parameter : defaultTrue)
		parameterCollection->SetParameter(parameter, true);

	for (const auto& parameter : defaultFalse)
		parameterCollection->SetParameter(parameter, false);
}

void GameObject::SetReferences(Systems* systems, IGameObjectContainer* gameObjectContainer)
{
	this->systems = systems;
	this->gameObjectContainer = gameObjectContainer;
}

void GameObject::Start()
{

}

void GameObject::Update()
{

}

ParameterCollection<GameObject::Parameters, GameObject::ParametersLength>* GameObject::GetParameterCollection() const
{
	return parameterCollection.get();
}

const string& GameObject::GetName() const
{
	return name;
}

void GameObject::SetName(const string& name)
{
	this->name = name;
}

string GameObject::GetGameObjectType() const
{
	return "GameObject";
}

ComponentContainer* GameObject::GetComponentContainer() const
{
	return components.get();
}

json GameObject::GetJson() const
{
	json gameObjectJson;
	gameObjectJson["type"] = GetGameObjectType();

	json componentJson;

	for (const auto transform : components->GetComponents<Transform>())
		componentJson[transform->GetName()] = transform->GetJson();

	for (const auto shading : components->GetComponents<Shading>())
		componentJson[shading->GetName()] = shading->GetJson();

	gameObjectJson["Components"] = componentJson;

	gameObjectJson["ParameterCollection"] = parameterCollection->GetJson();
	return gameObjectJson;
}

void GameObject::SetFromJson(const json& j)
{
	json componentObjects = j["Components"];

	for (const auto componentJson : componentObjects.items())
	{
		shared_ptr<Component> component = ComponentFactory::MakeComponent(componentJson.value()["type"]);
		AddComponent(component, componentJson.key())->SetFromJson(componentJson.value());
	}

	parameterCollection->SetFromJson(j["ParameterCollection"]);
}

void GameObject::ReceiveEvent(const string& key, const json& event)
{

}

GameObject::~GameObject()
{

}
