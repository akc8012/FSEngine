#pragma once
#include "Systems.h"
#include "ComponentContainer.h"
#include "ParameterCollection.h"
#include "IRenderable.h"
#include "INameable.h"
#include "ISerializable.h"
#include "IUpdatable.h"

class IGameObject : public IRenderable, public INameable, public ISerializable, public IUpdatable
{
public:
	virtual ~IGameObject()
	{

	}

	virtual void Start() = 0;
	virtual void SceneLoaded() = 0;

	enum Parameters { DoUpdate, DoDraw, DoLateUpdate, DoLateDraw, ParametersLength };
	virtual ParameterCollection<Parameters, ParametersLength>* GetParameterCollection() const = 0;

	virtual string GetGameObjectType() const = 0;
	virtual ComponentContainer* GetComponentContainer() const = 0;

	template <typename T>
	T* AddComponent(shared_ptr<T> component, const string& name = "");
	template <typename T>
	T* GetComponent(const string& name = "") const;
	template <typename T>
	T* TryGetComponent(const string& name = "") const;
};

template <typename T>
T* IGameObject::AddComponent(shared_ptr<T> component, const string& name)
{
	return GetComponentContainer()->AddComponent<T>(component, name);
}

template <typename T>
T* IGameObject::GetComponent(const string& name) const
{
	return GetComponentContainer()->GetComponent<T>(name);
}

template <typename T>
T* IGameObject::TryGetComponent(const string& name) const
{
	return GetComponentContainer()->TryGetComponent<T>(name);
}
