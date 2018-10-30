#pragma once
#include "Shading.h"
#include "ParameterCollection.h"

class Color : public Shading
{
private:
	vec4 color;

public:
	static const Types::ComponentType ComponentTypeId = Types::Color;
	Types::ComponentType GetComponentTypeId() const override;

	Color();
	Color(const vec3& color);
	Color(float r, float g, float b);
	Color(int r, int g, int b);

	void SetColor(const vec3& color);
	void SetColor(const vec4& color);
	vec4 GetColor() const override;

	json GetJson() const override;
	void SetFromJson(const json& j) override;
};
