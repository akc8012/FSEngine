#pragma once
#include "Drawable.h"
#include "ShaderProgram.h"
#include "ParameterCollection.h"

class Shading : public Drawable
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

	void SetFlatColor(const vec3& flatColor);
	void SetFlatColor(const vec4& flatColor);
	vec4 GetFlatColor() const override;

	json GetJson() const override;
	void SetFromJson(const json& j) override;
};
