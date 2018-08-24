#pragma once
#include <string>
using std::string;

template <typename Parameters, int CollectionLength>
class ParameterCollection
{
private:
	short parameters[CollectionLength];

	void SetParameter(Parameters parameter, short value);

public:
	ParameterCollection();

	void SetParameter(Parameters parameter, bool value);
	bool GetParameter(Parameters parameter) const;

	bool IsInitializedAndEqualTo(Parameters parameter, bool value) const;
	bool IsParameterInitialized(Parameters parameter) const;
};
