#pragma once
#include "IGameObject.h"

class IGameObjectContainer
{
public:
	virtual ~IGameObjectContainer()
	{

	}

	virtual IGameObject* AddGameObject(const string& name, unique_ptr<IGameObject> gameObject) = 0;
	virtual void RemoveGameObject(const string& name) = 0;

	virtual IGameObject* GetGameObject(const string& name) const = 0;
	virtual IGameObject* TryGetGameObject(const string& name) const = 0;

	virtual vector<IGameObject*> GetGameObjects() const = 0;
	virtual int GetGameObjectCount() const = 0;

	template <typename T>
	T* GetGameObjectAs(const string& name) const;
};

template <typename T>
T* IGameObjectContainer::GetGameObjectAs(const string& name) const
{
	return static_cast<T*>(GetGameObject(name));
}
