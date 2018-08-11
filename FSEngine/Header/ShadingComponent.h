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
	ShadingComponent(const vec4& flatColor);
	virtual ~ShadingComponent();

	virtual bool CanUse() const;
	virtual void Use(ShaderProgram* shaderProgram);

	void SetFlatColor(const vec4& flatColor);
	vec4 GetFlatColor() const;

	void SetDepthTest(bool enableDepthTest);
	bool GetDepthTest() const;
	void SetRenderPerspective(bool renderPerspective);
	bool GetRenderPerspective() const;
};
