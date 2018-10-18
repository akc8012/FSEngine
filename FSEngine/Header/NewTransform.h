#pragma once
#include "Component.h"

class NewTransform : public Component
{
private:

public:
	static const Types::ComponentType ComponentTypeId = Types::NewTransform;

	json GetJson() const override;
	void SetFromJson(const json& j) override;
};
