#pragma once
#include "IGameObject.h"
#include "FSException.h"
#include "Mesh.h"
#include "Shading.h"
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
	unique_ptr<ParameterCollection<Parameters, ParametersLength>> parameterCollection;

	void SetDefaultParameters();

protected:
	Systems* systems = nullptr;

public:
	GameObject();
	virtual ~GameObject();

	void SetReferences(Systems* systems, ComponentContainer* components);

	virtual void Start() override;
	virtual void Update() override;

	ParameterCollection<Parameters, ParametersLength>* GetParameterCollection() const override;

	const string& GetName() const override;
	void SetName(const string& name) override;

	json GetJson() const;
	void SetFromJson(const json& j);

	void ReceiveEvent(const string& key, const json& event) override;
};
