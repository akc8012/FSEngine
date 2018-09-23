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

void GameObject::SetSystems(Systems* systems, GameObject::GameObjectContainer* gameObjectContainer)
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

const shared_ptr<MeshComponent>& GameObject::AddComponent(const shared_ptr<MeshComponent>& component, const string& name)
{
	auto result = meshComponents.emplace(name, component);
	if (!result.second)
		ThrowDuplicateNameException(name);

	return component;
}

const shared_ptr<ShadingComponent>& GameObject::AddComponent(const shared_ptr<ShadingComponent>& component, const string& name)
{
	auto result = shadingComponents.emplace(name, component);
	if (!result.second)
		ThrowDuplicateNameException(name);

	return component;
}

const shared_ptr<TransformComponent>& GameObject::AddComponent(const shared_ptr<TransformComponent>& component, const string& name)
{
	auto result = transformComponents.emplace(name, component);
	if (!result.second)
		ThrowDuplicateNameException(name);

	return component;
}

void GameObject::ThrowDuplicateNameException(const string& name) const
{
	throwFS("Component with name " + name + " already exists");
}

ParameterCollection<GameObject::Parameters, GameObject::ParametersLength>* GameObject::GetParameterCollection() const
{
	return parameterCollection.get();
}

string GameObject::GetName() const
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
	for (const auto& transformComponent : transformComponents)
		j[transformComponent.first] = transformComponent.second->GetJson();

	for (const auto& shadingComponent : shadingComponents)
		j[shadingComponent.first] = shadingComponent.second->GetJson();

	j["ParameterCollection"] = parameterCollection->GetJson();
	return j;
}

void GameObject::SetFromJson(const json& j)
{
	for (auto& transformComponent : transformComponents)
		transformComponent.second->SetFromJson(j[transformComponent.first]);

	for (auto& shadingComponent : shadingComponents)
		shadingComponent.second->SetFromJson(j[shadingComponent.first]);

	parameterCollection->SetFromJson(j["ParameterCollection"]);
}

GameObject::~GameObject()
{

}
