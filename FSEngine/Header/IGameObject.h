#pragma once
#include "Systems.h"
#include "Components.h"
#include "ParameterCollection.h"

#include <string>
using std::string;

class IGameObject
{
public:
	virtual ~IGameObject()
	{

	}

	virtual void SetReferences(Systems* systems, Components* components) = 0;

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
};
