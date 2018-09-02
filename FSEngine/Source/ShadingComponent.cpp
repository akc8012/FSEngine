#include "../Header/ShadingComponent.h"

ShadingComponent::ShadingComponent()
{
	flatColor = vec4(0);
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

ShadingComponent::ShadingComponent(int r, int g, int b)
{
	SetFlatColor(vec3((float)r, (float)g, (float)b));
	Initialize();
}

void ShadingComponent::Initialize()
{
	parameterCollection = make_unique<ParameterCollection<Parameters, ParametersLength>>();
	parameterCollection->SetParameter(EnableDepthTest, true);
	parameterCollection->SetParameter(RenderPerspective, true);
	parameterCollection->SetParameter(Blend, true);
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
	return parameterCollection.get();
}
