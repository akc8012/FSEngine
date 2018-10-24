#pragma once
#include "Component.h"
#include "ParameterCollection.h"

class Drawable : public Component
{
public:
	enum Parameters
	{
		EnableDepthTest,
		RenderPerspective,
		Blend,

		ParametersLength
	};

private:
	unique_ptr<ParameterCollection<Parameters, ParametersLength>> parameterCollection;

public:
	Drawable();
	virtual ~Drawable();

	virtual void BindTexture() = 0;
	virtual bool HasFlatColor() const = 0;

	virtual json GetJson() const override;
	virtual void SetFromJson(const json& j) override;

	ParameterCollection<Parameters, ParametersLength>* GetParameterCollection() const;
};
