#pragma once
#include "FSException.h"
#include "Systems.h"
#include "Mesh.h"
#include "Shading.h"
#include "Texture.h"
#include "Transform.h"
#include "Components.h"
#include "ParameterCollection.h"

#include <typeinfo>
using std::shared_ptr;
using std::make_shared;

class GameObject
{
public:
	enum Parameters
	{
		DoUpdate,
		DoDraw,
		DoLateUpdate,
		DoLateDraw,

		ParametersLength
	};

private:
	string name;
	unique_ptr<ParameterCollection<Parameters, ParametersLength>> parameterCollection;

	void SetDefaultParameters();

protected:
	Systems* systems = nullptr;
	Components* components = nullptr;

public:
	GameObject();
	virtual ~GameObject();

	void SetReferences(Systems* systems, Components* components);

	virtual void Start();
	virtual void Update();

	ParameterCollection<Parameters, ParametersLength>* GetParameterCollection() const;

	template <typename T>
	T* GetComponent(const string& name = "") const;
	template <typename T>
	T* TryGetComponent(const string& name = "") const;

	const string& GetName() const;
	void SetName(const string& name);

	json GetJson() const;
	void SetFromJson(const json& j);
};

template<typename T>
T* GameObject::GetComponent(const string& name) const
{
	auto component = TryGetComponent<T>(name);
	if (component == nullptr)
		throwFS("Could not find component on GameObject \"" + GetName() + "\" with name \"" + name + "\"");

	return component;
}

template<typename T>
T* GameObject::TryGetComponent(const string& name) const
{
	if (typeid(T) == typeid(Mesh))
		return reinterpret_cast<T*>(name == "" ? components->mesh->TryGet(GetName()).get() : components->mesh->TryGet(GetName(), name).get());

	if (typeid(T) == typeid(Shading))
		return reinterpret_cast<T*>(name == "" ? components->shading->TryGet(GetName()).get() : components->shading->TryGet(GetName(), name).get());

	if (typeid(T) == typeid(Transform))
		return reinterpret_cast<T*>(name == "" ? components->transform->TryGet(GetName()).get() : components->transform->TryGet(GetName(), name).get());

	throwFS("Unknown type used for GetComponent");
}
