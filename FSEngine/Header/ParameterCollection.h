#pragma once
#include "FSException.h"

#include <nlohmann\json.hpp>
using json = nlohmann::json;

#include <string>
#include <algorithm>
using std::string;

template <typename Parameters, int CollectionLength>
class ParameterCollection
{
private:
	short parameters[CollectionLength];
	string parameterNames[CollectionLength];

	void SetParameter(Parameters parameter, short value)
	{
		parameters[parameter] = value;
	}

public:
	void ReInitializeParameters()
	{
		for (auto& parameter : parameters)
			parameter = -1;
	}

	ParameterCollection(string parameterNames[CollectionLength])
	{
		for (int i = 0; i < CollectionLength; i++)
			this->parameterNames[i] = parameterNames[i];

		ReInitializeParameters();
	}

	void SetParameter(Parameters parameter, bool value)
	{
		SetParameter(parameter, (short)value);
	}

	void UninitializeParameter(Parameters parameter)
	{
		SetParameter(parameter, (short)-1);
	}

	bool GetParameter(Parameters parameter) const
	{
		if (!IsParameterInitialized(parameter))
			throwFS("Trying to access uninitialized parameter: " + parameterNames[parameter]);

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

	json GetJson() const
	{
		json j;
		for (int i = 0; i < CollectionLength; i++)
			j[parameterNames[i]] = parameters[i];

		return j;
	}

	void SetFromJson(const json& j)
	{
		for (int i = 0; i < CollectionLength; i++)
		{
			string name = parameterNames[i];
			int index = (int)std::distance(parameterNames, std::find(parameterNames, parameterNames + CollectionLength, name));

			parameters[index] = j[name];
		}
	}
};
