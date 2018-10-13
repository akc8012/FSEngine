#pragma once
#include "IGameObject.h"
#include "FSException.h"
#include "Mesh.h"
#include "Shading.h"
#include "Texture.h"
#include "Transform.h"
#include "IEventListener.h"

#include <typeinfo>
using std::shared_ptr;
using std::make_shared;

class GameObject : public IGameObject, public IEventListener
{
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

	void SetReferences(Systems* systems, Components* components) override;

	virtual void Start() override;
	virtual void Update() override;

	ParameterCollection<Parameters, ParametersLength>* GetParameterCollection() const override;

	template <typename T>
	T* GetComponent(const string& name = "") const;
	template <typename T>
	T* TryGetComponent(const string& name = "") const;

	const string& GetName() const override;
	void SetName(const string& name) override;

	json GetJson() const;
	void SetFromJson(const json& j);

	void ReceiveEvent(const string& key, const json& event) override;
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
		return reinterpret_cast<T*>(name == "" ? components->mesh->TryGet(GetName()) : components->mesh->TryGet(GetName(), name));

	if (typeid(T) == typeid(Shading))
		return reinterpret_cast<T*>(name == "" ? components->shading->TryGet(GetName()) : components->shading->TryGet(GetName(), name));

	if (typeid(T) == typeid(Transform))
		return reinterpret_cast<T*>(name == "" ? components->transform->TryGet(GetName()) : components->transform->TryGet(GetName(), name));

	throwFS("Unknown type used for GetComponent");
}
