#include "../Header/Shading.h"

Shading::Shading()
{
	flatColor = vec4(0);
	Initialize();
}

Shading::Shading(const vec3& flatColor)
{
	SetFlatColor(flatColor);
	Initialize();
}

Shading::Shading(float r, float g, float b)
{
	SetFlatColor(vec3(r, g, b));
	Initialize();
}

Shading::Shading(int r, int g, int b)
{
	SetFlatColor(vec3((float)r, (float)g, (float)b));
	Initialize();
}

void Shading::Initialize()
{
	string parameterNames[] = { "EnableDepthTest", "RenderPerspective", "Blend" };
	parameterCollection = make_unique<ParameterCollection<Parameters, ParametersLength>>(parameterNames);

	parameterCollection->SetParameter(EnableDepthTest, true);
	parameterCollection->SetParameter(RenderPerspective, true);
	parameterCollection->SetParameter(Blend, true);
}

void Shading::BindTexture()
{
	glBindTexture(GL_TEXTURE_2D, NULL);
}

void Shading::SetFlatColor(const vec3& flatColor)
{
	this->flatColor = vec4(flatColor, 1.0f);
}

vec4 Shading::GetFlatColor() const
{
	return flatColor;
}

ParameterCollection<Shading::Parameters, Shading::ParametersLength>* Shading::GetParameterCollection() const
{
	return parameterCollection.get();
}
