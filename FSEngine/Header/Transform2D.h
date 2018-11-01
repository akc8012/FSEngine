#pragma once
#include "Transform.h"

class Transform2D : public Transform
{
private:

public:
	static const Types::ComponentType ComponentTypeId = Types::Transform2D;
	Types::ComponentType GetComponentTypeId() const override;

};
