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

bool Shading::HasFlatColor() const
{
	return true;
}

void Shading::SetFlatColor(const vec3& flatColor)
{
	SetFlatColor(vec4(flatColor, 1.0f));
}

void Shading::SetFlatColor(const vec4& flatColor)
{
	this->flatColor = flatColor;
}

vec4 Shading::GetFlatColor() const
{
	return flatColor;
}

json Shading::GetJson() const
{
	json j;
	j["type"] = Types::ComponentTypeString[ComponentTypeId];
	j["FlatColor"] = { flatColor.r, flatColor.g, flatColor.b, flatColor.a };
	j["ParameterCollection"] = parameterCollection->GetJson();

	return j;
}

void Shading::SetFromJson(const json& j)
{
	json flatColor = j["FlatColor"];
	SetFlatColor(vec4(flatColor[0], flatColor[1], flatColor[2], flatColor[3]));

	parameterCollection->SetFromJson(j["ParameterCollection"]);
}

Types::ComponentType Shading::GetComponentTypeId() const
{
	return ComponentTypeId;
}
