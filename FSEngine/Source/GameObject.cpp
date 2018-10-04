#include "../Header/GameObject.h"

GameObject::GameObject()
{
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

void GameObject::SetReferences(Systems* systems, GameObject::GameObjectContainer* gameObjectContainer, Components* components)
{
	this->systems = systems;
	this->gameObjectContainer = gameObjectContainer;
	this->components = components;
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

json GameObject::GetJson() const
{
	json j;
	j["ParameterCollection"] = parameterCollection->GetJson();

	return j;
}

void GameObject::SetFromJson(const json& j)
{
	parameterCollection->SetFromJson(j["ParameterCollection"]);
}

GameObject::~GameObject()
{

}
