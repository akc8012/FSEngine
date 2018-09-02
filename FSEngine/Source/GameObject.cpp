#include "../Header/GameObject.h"

GameObject::GameObject()
{
	parameterCollection = make_unique<ParameterCollection<Parameters, ParametersLength>>();
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

MeshComponent* GameObject::AddComponent(MeshComponent* component, string name)
{
	auto result = meshComponents.emplace(name, shared_ptr<MeshComponent>(component));
	if (!result.second)
		ThrowDuplicateNameException(name);

	return component;
}

ShadingComponent* GameObject::AddComponent(ShadingComponent* component, string name)
{
	auto result = shadingComponents.emplace(name, shared_ptr<ShadingComponent>(component));
	if (!result.second)
		ThrowDuplicateNameException(name);

	return component;
}

TransformComponent* GameObject::AddComponent(TransformComponent* component, string name)
{
	auto result = transformComponents.emplace(name, shared_ptr<TransformComponent>(component));
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

const string& GameObject::GetName() const
{
	return *name;
}

void GameObject::SetName(const string& name)
{
	this->name = &name;
}
