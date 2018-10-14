#pragma once
#include "Systems.h"
#include "ComponentContainer.h"
#include "ParameterCollection.h"

#include <string>
using std::string;

class IGameObject
{
protected:
	unique_ptr<ComponentContainer> components;

public:
	virtual ~IGameObject()
	{

	}

	virtual void Start() = 0;
	virtual void Update() = 0;

	enum Parameters
	{
		DoUpdate,
		DoDraw,
		DoLateUpdate,
		DoLateDraw,

		ParametersLength
	};
	virtual ParameterCollection<Parameters, ParametersLength>* GetParameterCollection() const = 0;

	virtual const string& GetName() const = 0;
	virtual void SetName(const string& name) = 0;

	virtual ComponentContainer* GetComponentContainer() const = 0;

	template <typename T>
	T* AddComponent(shared_ptr<T> component, const string& name = "") const;
	template <typename T>
	T* GetComponent(const string& name = "") const;
	template <typename T>
	T* TryGetComponent(const string& name = "") const;
};

template <typename T>
T* IGameObject::AddComponent(shared_ptr<T> component, const string& name) const
{
	return components->AddComponent(component, name);
}

template <typename T>
T* IGameObject::GetComponent(const string& name) const
{
	return components->GetComponent<T>(name);
}

template <typename T>
T* IGameObject::TryGetComponent(const string& name) const
{
	return components->TryGetComponent<T>(name);
}
