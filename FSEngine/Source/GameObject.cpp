#include "../Header/GameObject.h"

GameObject::GameObject()
{
	parameterCollection = make_unique<ParameterCollection<Parameters, ParametersLength>>();
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

void GameObject::Update()
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

GameObject::~GameObject()
{
	for (auto& meshComponent : meshComponents)
		delete meshComponent.second;

	for (auto& textureComponent : shadingComponents)
		delete textureComponent.second;

	for (auto& transformComponent : transformComponents)
		delete transformComponent.second;
}
