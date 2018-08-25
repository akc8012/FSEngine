#pragma once
#include <string>
using std::string;

template <typename Parameters, int CollectionLength>
class ParameterCollection
{
private:
	short parameters[CollectionLength];

	void SetParameter(Parameters parameter, short value)
	{
		parameters[parameter] = value;
	}

public:
	ParameterCollection()
	{
		for (auto& parameter : parameters)
			parameter = -1;
	}

	void SetParameter(Parameters parameter, bool value)
	{
		SetParameter(parameter, (short)value);
	}

	bool GetParameter(Parameters parameter) const
	{
		if (!IsParameterInitialized(parameter))
			throw (string)"Trying to access uninitialized parameter: " + std::to_string(parameter);

		return (bool)parameters[parameter];
	}

	bool IsInitializedAndEqualTo(Parameters parameter, bool value) const
	{
		return IsParameterInitialized(parameter) && GetParameter(parameter) == value;
	}

	bool IsParameterInitialized(Parameters parameter) const
	{
		return parameters[parameter] != (short)-1;
	}
};
