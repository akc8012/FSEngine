#pragma once
#include "Systems.h"
#include "ComponentContainer.h"
#include "ParameterCollection.h"
#include "IRenderable.h"

#include <string>
using std::string;

class IGameObject : public IRenderable
{
public:
	virtual ~IGameObject()
	{

	}

	virtual void Start() = 0;
	virtual void SceneLoaded() = 0;
	virtual void Update() = 0;

	enum Parameters { DoUpdate, DoDraw, DoLateUpdate, DoLateDraw, ParametersLength };
	virtual ParameterCollection<Parameters, ParametersLength>* GetParameterCollection() const = 0;

	virtual const string& GetName() const = 0;
	virtual void SetName(const string& name) = 0;
	virtual string GetGameObjectType() const = 0;

	virtual ComponentContainer* GetComponentContainer() const = 0;

	virtual json GetJson() const = 0;
	virtual void SetFromJson(const json& j) = 0;

	template <typename T>
	T* AddComponent(shared_ptr<T> component, const string& name = "");
	template <typename T>
	T* GetComponent(const string& name = "") const;
	template <typename T>
	T* TryGetComponent(const string& name = "") const;

	virtual void SetSerializable(bool serializable) = 0;
	virtual bool GetSerializable() const = 0;
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
