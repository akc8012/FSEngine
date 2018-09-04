#pragma once
#include "Component.h"
#include "ShaderProgram.h"
#include "ParameterCollection.h"

#include <glm\glm.hpp>
using glm::vec4;
using glm::vec3;

class ShadingComponent : public Component
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
	vec4 flatColor;

	void Initialize();

public:
	static const ComponentType ComponentTypeId = Shading;

	ShadingComponent();
	ShadingComponent(const vec3& flatColor);
	ShadingComponent(float r, float g, float b);
	ShadingComponent(int r, int g, int b);

	virtual void BindTexture();

	void SetFlatColor(const vec3& flatColor);
	vec4 GetFlatColor() const;

	ParameterCollection<Parameters, ParametersLength>* GetParameterCollection() const;
};
