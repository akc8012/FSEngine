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

ComponentContainer* GameObject::GetComponentContainer() const
{
	return components.get();
}

json GameObject::GetJson() const
{
	json j;
	for (const auto transform : components->GetComponents<Transform>())
		j[transform->GetName()] = transform->GetJson();

	for (const auto shading : components->GetComponents<Shading>())
		j[shading->GetName()] = shading->GetJson();

	j["ParameterCollection"] = parameterCollection->GetJson();
	return j;
}

void GameObject::SetFromJson(const json& j)
{
	for (auto transform : components->GetComponents<Transform>())
		transform->SetFromJson(j[transform->GetName()]);

	for (auto shading : components->GetComponents<Shading>())
		shading->SetFromJson(j[shading->GetName()]);

	parameterCollection->SetFromJson(j["ParameterCollection"]);
}

void GameObject::ReceiveEvent(const string& key, const json& event)
{

}

GameObject::~GameObject()
{

}
