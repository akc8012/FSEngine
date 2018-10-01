#pragma once
#include "Component.h"
#include "ShaderProgram.h"
#include "ParameterCollection.h"

#include <glm\glm.hpp>
using glm::vec4;
using glm::vec3;

class Shading : public Component
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
	static const Types::ComponentType ComponentTypeId = Types::Shading;

	Shading();
	Shading(const vec3& flatColor);
	Shading(float r, float g, float b);
	Shading(int r, int g, int b);

	virtual void BindTexture();

	void SetFlatColor(const vec3& flatColor);
	void SetFlatColor(const vec4& flatColor);
	vec4 GetFlatColor() const;

	ParameterCollection<Parameters, ParametersLength>* GetParameterCollection() const;

	virtual json GetJson() const override;
	virtual void SetFromJson(const json& j) override;
};
