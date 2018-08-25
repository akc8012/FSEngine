#include "../Header/ShadingComponent.h"

ShadingComponent::ShadingComponent()
{
	Initialize();
}

ShadingComponent::ShadingComponent(const vec3& flatColor)
{
	SetFlatColor(flatColor);
	Initialize();
}

ShadingComponent::ShadingComponent(float r, float g, float b)
{
	SetFlatColor(vec3(r, g, b));
	Initialize();
}

void ShadingComponent::Initialize()
{
	parameterCollection = new ParameterCollection<Parameters, ParametersLength>();
	parameterCollection->SetParameter(EnableDepthTest, true);
	parameterCollection->SetParameter(RenderPerspective, true);
}

void ShadingComponent::BindTexture()
{
	glBindTexture(GL_TEXTURE_2D, NULL);
}

void ShadingComponent::SetFlatColor(const vec3& flatColor)
{
	this->flatColor = vec4(flatColor, 1.0f);
}

vec4 ShadingComponent::GetFlatColor() const
{
	return flatColor;
}

ParameterCollection<ShadingComponent::Parameters, ShadingComponent::ParametersLength>* ShadingComponent::GetParameterCollection() const
{
	return parameterCollection;
}

ShadingComponent::~ShadingComponent()
{
	delete parameterCollection;
}
