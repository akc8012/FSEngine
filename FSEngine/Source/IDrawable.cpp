#include "../Header/IDrawable.h"

IDrawable::~IDrawable()
{

}

ParameterCollection<IDrawable::Parameters, IDrawable::ParametersLength>* IDrawable::GetParameterCollection() const
{
	return parameterCollection.get();
}
