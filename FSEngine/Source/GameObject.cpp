#include "../Header/GameObject.h"

GameObject::GameObject()
{
	parameterCollection = new ParameterCollection<Parameters, ParametersLength>();
	SetDefaultParameters();

	meshComponents = unordered_map<string, MeshComponent*>();
	shadingComponents = unordered_map<string, ShadingComponent*>();
	transformComponents = unordered_map<string, TransformComponent*>();
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

void GameObject::Update(float deltaTime)
{

}

MeshComponent* GameObject::AddComponent(MeshComponent* component, string name)
{
	auto result = meshComponents.emplace(name, component);
	if (!result.second)
		ThrowDuplicateNameException(name);

	return component;
}

ShadingComponent* GameObject::AddComponent(ShadingComponent* component, string name)
{
	auto result = shadingComponents.emplace(name, component);
	if (!result.second)
		ThrowDuplicateNameException(name);

	return component;
}

TransformComponent* GameObject::AddComponent(TransformComponent* component, string name)
{
	auto result = transformComponents.emplace(name, component);
	if (!result.second)
		ThrowDuplicateNameException(name);

	return component;
}

void GameObject::ThrowDuplicateNameException(const string& name) const
{
	throw "Component with name " + name + " already exists";
}

ParameterCollection<GameObject::Parameters, GameObject::ParametersLength>* GameObject::GetParameterCollection() const
{
	return parameterCollection;
}

GameObject::~GameObject()
{
	for (auto& meshComponent : meshComponents)
	{
		if (!meshComponent.second->IsShared())
			delete meshComponent.second;
	}

	for (auto& textureComponent : shadingComponents)
	{
		if (!textureComponent.second->IsShared())
			delete textureComponent.second;
	}

	for (auto& transformComponent : transformComponents)
	{
		if (!transformComponent.second->IsShared())
			delete transformComponent.second;
	}

	delete parameterCollection;
}
