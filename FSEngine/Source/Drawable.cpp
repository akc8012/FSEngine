#include "../Header/Drawable.h"

Drawable::Drawable()
{
	string parameterNames[] = { "EnableDepthTest", "RenderPerspective", "Blend" };
	parameterCollection = make_unique<ParameterCollection<Parameters, ParametersLength>>(parameterNames);

	parameterCollection->SetParameter(EnableDepthTest, true);
	parameterCollection->SetParameter(RenderPerspective, true);
	parameterCollection->SetParameter(Blend, true);
}

vec4 Drawable::GetColor() const
{
	return vec4(0);
}

json Drawable::GetJson() const
{
	json j = Component::GetJson();
	j["ParameterCollection"] = parameterCollection->GetJson();
	return j;
}

void Drawable::SetFromJson(const json& j)
{
	Component::SetFromJson(j);
	parameterCollection->SetFromJson(j["ParameterCollection"]);
}

ParameterCollection<Drawable::Parameters, Drawable::ParametersLength>* Drawable::GetParameterCollection() const
{
	return parameterCollection.get();
}

Drawable::~Drawable()
{

}
