#pragma once
#include "IDrawable.h"
#include "ShaderProgram.h"
#include "ParameterCollection.h"

#include <glm\glm.hpp>
using glm::vec4;
using glm::vec3;

class Shading : public IDrawable
{
private:
	vec4 flatColor;

public:
	static const Types::ComponentType ComponentTypeId = Types::Shading;
	Types::ComponentType GetComponentTypeId() const override;

	Shading();
	Shading(const vec3& flatColor);
	Shading(float r, float g, float b);
	Shading(int r, int g, int b);

	void BindTexture() override;
	bool HasFlatColor() const override;

	void SetFlatColor(const vec3& flatColor);
	void SetFlatColor(const vec4& flatColor);
	vec4 GetFlatColor() const;

	json GetJson() const override;
	void SetFromJson(const json& j) override;
};
