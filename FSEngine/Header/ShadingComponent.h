#pragma once
#include "Component.h"
#include "ShaderProgram.h"

#include <glm\glm.hpp>
using namespace glm;

class ShadingComponent : public Component
{
private:
	vec4 flatColor = vec4(0);
	bool enableDepthTest = true;
	bool renderPerspective = true;

public:
	static const ComponentType ComponentTypeId = Shading;

	ShadingComponent();
	ShadingComponent(const vec3& flatColor);
	ShadingComponent(float r, float g, float b);
	virtual ~ShadingComponent();

	virtual void BindTexture();

	void SetFlatColor(const vec3& flatColor);
	vec4 GetFlatColor() const;

	void SetDepthTest(bool enableDepthTest);
	bool EnableDepthTest() const;

	void SetRenderPerspective(bool renderPerspective);
	bool GetRenderPerspective() const;
};
