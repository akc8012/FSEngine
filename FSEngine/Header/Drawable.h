#pragma once
#include "Component.h"
#include "ParameterCollection.h"

#include <glm\glm.hpp>
using glm::vec4;
using glm::vec3;

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
	virtual vec4 GetColor() const; // TODO: BETTER WAY OF HANDLING THIS

	virtual json GetJson() const override;
	virtual void SetFromJson(const json& j) override;

	ParameterCollection<Parameters, ParametersLength>* GetParameterCollection() const;
};
