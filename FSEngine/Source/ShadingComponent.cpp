#include "../Header/ShadingComponent.h"

ShadingComponent::ShadingComponent()
{

}

ShadingComponent::ShadingComponent(const vec4& flatColor)
{
	SetFlatColor(flatColor);
}

void ShadingComponent::SetFlatColor(const vec4& flatColor)
{
	this->flatColor = flatColor;
}

bool ShadingComponent::CanUse() const
{
	return true;
}

void ShadingComponent::Use(ShaderProgram* shaderProgram)
{
	shaderProgram->SetVector("flatColor", flatColor);
}

vec4 ShadingComponent::GetFlatColor() const
{
	return flatColor;
}

ShadingComponent::~ShadingComponent()
{

}
