#include "../Header/ParameterCollection.h"

template <typename Parameters, int CollectionLength>
ParameterCollection<Parameters, CollectionLength>::ParameterCollection()
{
	for (const auto& parameter : parameters)
		parameter = -1;
};

template<typename Parameters, int CollectionLength>
void ParameterCollection<Parameters, CollectionLength>::SetParameter(Parameters parameter, bool value)
{
	SetParameter(parameter, (short)value);
}

template<typename Parameters, int CollectionLength>
void ParameterCollection<Parameters, CollectionLength>::SetParameter(Parameters parameter, short value)
{
	parameters[parameter] = value;
}

template<typename Parameters, int CollectionLength>
bool ParameterCollection<Parameters, CollectionLength>::GetParameter(Parameters parameter) const
{
	if (!IsParameterInitialized(parameter))
		throw (string)"Trying to access uninitialized parameter: " + std::to_string(parameter);

	return (bool)parameters[parameter];
}

template<typename Parameters, int CollectionLength>
bool ParameterCollection<Parameters, CollectionLength>::IsInitializedAndEqualTo(Parameters parameter, bool value) const
{
	return IsParameterInitialized(parameter) && GetParameter(parameter) == value;
}

template<typename Parameters, int CollectionLength>
bool ParameterCollection<Parameters, CollectionLength>::IsParameterInitialized(Parameters parameter) const
{
	return parameters[parameter] != (short)-1;
}
