#include "../Header/Shading.h"

Shading::Shading()
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

vec4 Shading::GetColor() const
{
	return vec4(0);
}

json Shading::GetJson() const
{
	json j = Component::GetJson();
	j["ParameterCollection"] = parameterCollection->GetJson();
	return j;
}

void Shading::SetFromJson(const json& j)
{
	Component::SetFromJson(j);
	parameterCollection->SetFromJson(j["ParameterCollection"]);
}

ParameterCollection<Shading::Parameters, Shading::ParametersLength>* Shading::GetParameterCollection() const
{
	return parameterCollection.get();
}

Shading::~Shading()
{

}
