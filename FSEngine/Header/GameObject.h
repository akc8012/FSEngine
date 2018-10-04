#pragma once
#include "FSException.h"
#include "Systems.h"
#include "Mesh.h"
#include "Shading.h"
#include "Texture.h"
#include "Transform.h"
#include "Components.h"
#include "GameObjectMapper.h"
#include "ParameterCollection.h"

using std::shared_ptr;
using std::make_shared;

#pragma region GameObject
class GameObject
{
public:
	class GameObjectContainer;
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
	GameObjectContainer* gameObjectContainer = nullptr;
	Components* components = nullptr;

public:
	GameObject();
	virtual ~GameObject();

	void SetReferences(Systems* systems, GameObject::GameObjectContainer* gameObjectContainer, Components* components);

	virtual void Start();
	virtual void Update();

	ParameterCollection<Parameters, ParametersLength>* GetParameterCollection() const;

	const string& GetName() const;
	void SetName(const string& name);

	json GetJson() const;
	void SetFromJson(const json& j);
};
#pragma endregion

#pragma region GameObjectContainer
class GameObject::GameObjectContainer
{
private:
	Systems* systems = nullptr;
	Components* components = nullptr;

	unique_ptr<GameObjectMapper> gameObjectMapper;
	vector<unique_ptr<GameObject>> gameObjects;

	void InitializeGameObject(GameObject* gameObject, const string& name);
	GameObject* TryGetGameObjectAtIndex(int index) const;

	void ReMapGameObjectNames(int startIndex);

public:
	GameObjectContainer(Systems* systems, Components* components);

	GameObject* AddGameObject(const string& name, GameObject* gameObject);
	void RemoveGameObject(const string& name);

	GameObject* GetGameObject(const string& name) const;
	GameObject* TryGetGameObject(const string& name) const;
	template <typename T> T* GetGameObjectAs(const string& name) const;

	const vector<unique_ptr<GameObject>>& GetGameObjects() const;
};

template <typename T> T* GameObject::GameObjectContainer::GetGameObjectAs(const string& name) const
{
	return dynamic_cast<T*>(GetGameObject(name));
}
#pragma endregion
