#pragma once
#include "Component.h"
#include "ParameterCollection.h"

class IDrawable : public Component
{
public:
	enum Parameters
	{
		EnableDepthTest,
		RenderPerspective,
		Blend,

		ParametersLength
	};

protected:
	unique_ptr<ParameterCollection<Parameters, ParametersLength>> parameterCollection;

public:
	virtual ~IDrawable();

	virtual void BindTexture() = 0;
	virtual bool HasFlatColor() const = 0;

	ParameterCollection<Parameters, ParametersLength>* GetParameterCollection() const;
};
