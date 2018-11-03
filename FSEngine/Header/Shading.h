#pragma once
#include "Component.h"
#include "ParameterCollection.h"

#include <SDL.h>
#include <GL\glew.h>
#include <SDL_opengl.h>

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
		CalculateLighting,
		Blend,

		ParametersLength
	};

private:
	unique_ptr<ParameterCollection<Parameters, ParametersLength>> parameterCollection;

public:
	static const Types::ComponentType ComponentTypeId = Types::Shading;
	virtual Types::ComponentType GetComponentTypeId() const override;

	Shading();
	virtual ~Shading();

	virtual void BindTexture();
	virtual vec4 GetColor() const;

	virtual json GetJson() const override;
	virtual void SetFromJson(const json& j) override;

	ParameterCollection<Parameters, ParametersLength>* GetParameterCollection() const;
};
