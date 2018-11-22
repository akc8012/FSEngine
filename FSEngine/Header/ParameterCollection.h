#pragma once
#include "ISerializable.h"
#include "FSException.h"

#include <string>
#include <algorithm>
using std::string;

template <typename Parameters, int CollectionLength>
class ParameterCollection : public ISerializable
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

	json GetJson() const override
	{
		json j;
		for (int i = 0; i < CollectionLength; i++)
			j[parameterNames[i]] = parameters[i];

		return j;
	}

	void SetFromJson(const json& j) override
	{
		for (int i = 0; i < CollectionLength; i++)
		{
			string name = parameterNames[i];
			int index = (int)std::distance(parameterNames, std::find(parameterNames, parameterNames + CollectionLength, name));

			parameters[index] = j[name];
		}
	}

	void SetSerializable(bool serializable) override
	{

	}

	bool GetSerializable() const override
	{
		return true;
	}
};
