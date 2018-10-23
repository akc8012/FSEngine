#include "../Header/IDrawable.h"

IDrawable::IDrawable()
{
	string parameterNames[] = { "EnableDepthTest", "RenderPerspective", "Blend" };
	parameterCollection = make_unique<ParameterCollection<Parameters, ParametersLength>>(parameterNames);

	parameterCollection->SetParameter(EnableDepthTest, true);
	parameterCollection->SetParameter(RenderPerspective, true);
	parameterCollection->SetParameter(Blend, true);

}

json IDrawable::GetJson() const
{
	json j;
	j["ParameterCollection"] = parameterCollection->GetJson();
	return j;
}

void IDrawable::SetFromJson(const json& j)
{
	parameterCollection->SetFromJson(j["ParameterCollection"]);
}

ParameterCollection<IDrawable::Parameters, IDrawable::ParametersLength>* IDrawable::GetParameterCollection() const
{
	return parameterCollection.get();
}

IDrawable::~IDrawable()
{

}
