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

const shared_ptr<Mesh>& GameObject::AddComponent(const shared_ptr<Mesh>& component, const string& name)
{
	auto result = meshComponents.emplace(name, component);
	if (!result.second)
		ThrowDuplicateNameException(name);

	return component;
}

const shared_ptr<Shading>& GameObject::AddComponent(const shared_ptr<Shading>& component, const string& name)
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

GameObject::~GameObject()
{

}
