#include "../Header/ShadingComponent.h"

ShadingComponent::ShadingComponent()
{

}

ShadingComponent::ShadingComponent(const vec3& flatColor)
{
	SetFlatColor(flatColor);
}

ShadingComponent::ShadingComponent(float r, float g, float b)
{
	SetFlatColor(vec3(r, g, b));
}

void ShadingComponent::BindTexture()
{

}

void ShadingComponent::SetFlatColor(const vec3& flatColor)
{
	this->flatColor = vec4(flatColor, 1.0f);
}

vec4 ShadingComponent::GetFlatColor() const
{
	return flatColor;
}

void ShadingComponent::SetDepthTest(bool enableDepthTest)
{
	this->enableDepthTest = enableDepthTest;
}

bool ShadingComponent::EnableDepthTest() const
{
	return enableDepthTest;
}

void ShadingComponent::SetRenderPerspective(bool renderPerspective)
{
	this->renderPerspective = renderPerspective;
}

bool ShadingComponent::GetRenderPerspective() const
{
	return renderPerspective;
}

ShadingComponent::~ShadingComponent()
{

}
