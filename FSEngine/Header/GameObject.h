#pragma once
#include "IGameObject.h"
#include "IGameObjectContainer.h"
#include "FSException.h"
#include "Mesh.h"
#include "Color.h"
#include "Texture.h"
#include "Transform.h"
#include "ComponentContainer.h"
#include "ParameterCollection.h"
#include "IEventListener.h"

using std::shared_ptr;
using std::make_shared;

class GameObject : public IGameObject, public IEventListener
{
private:
	string name;
	bool serializable = true;
	unique_ptr<ComponentContainer> components;
	unique_ptr<ParameterCollection<Parameters, ParametersLength>> parameterCollection;

	void SetDefaultParameters();

	void RemoveUnloadedComponents(const json& componentObjects);
	bool ComponentMatchesType(const json& foundComponent, const Component* loadedComponent) const;

	Component* TryGetComponentOfType(const string& type, const string& name);

protected:
	Systems* systems = nullptr;
	IGameObjectContainer* gameObjectContainer = nullptr;

public:
	GameObject();
	virtual ~GameObject();

	void SetReferences(Systems* systems, IGameObjectContainer* gameObjectContainer);

	virtual void Start() override;
	virtual void SceneLoaded() override;
	virtual void Update() override;

	ParameterCollection<Parameters, ParametersLength>* GetParameterCollection() const override;

	const string& GetName() const override;
	void SetName(const string& name) override;

	ComponentContainer* GetComponentContainer() const override;

	virtual json GetJson() const override;
	virtual void SetFromJson(const json& j) override;

	void SetSerializable(bool serializable) override;
	bool GetSerializable() const override;

	virtual ComponentCollection<Mesh>* GetMeshCollection() const override;
	virtual ComponentCollection<Texture>* GetTextureCollection() const override;

	void ReceiveEvent(const string& key, const json& event) override;
};
