#pragma once
#include "FSException.h"
#include "Systems.h"
#include "Mesh.h"
#include "Shading.h"
#include "Texture.h"
#include "Transform.h"
#include "ComponentContainer.h"
#include "ParameterCollection.h"
#include "IEventListener.h"

using std::shared_ptr;
using std::make_shared;

class GameObject : public IEventListener
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
	ComponentContainer* components = nullptr;

public:
	GameObject();
	virtual ~GameObject();

	void SetReferences(Systems* systems, ComponentContainer* components);

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

	void ReceiveEvent(const string& key, const json& event) override;
};

template <typename T>
T* GameObject::GetComponent(const string& name) const
{
	return components->GetComponent<T>(GetName(), name);
}

template <typename T>
T* GameObject::TryGetComponent(const string& name) const
{
	return components->TryGetComponent<T>(GetName(), name);
}
