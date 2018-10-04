#pragma once
#include "FSException.h"
#include "Systems.h"
#include "Mesh.h"
#include "Shading.h"
#include "Texture.h"
#include "Transform.h"
#include "Components.h"
#include "ParameterCollection.h"

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

	const string& GetName() const;
	void SetName(const string& name);

	json GetJson() const;
	void SetFromJson(const json& j);
};
